/* DSA Journal — static single-page app. Data lives in data/ and problems/. */
const INTERVALS = [1, 3, 7, 14, 30, 60];          // days until next review, by box
const DAILY_CAP = 5;                              // most revisions scheduled on any one day
const NEW_PER_DAY = 5;                            // new problems a profile's plan gives each day
const PROFILES_KEY = 'dsa-journal-profiles-v1';  // { active, list: [{ id, name, start }] }
const LIMIT_MIN = { Easy: 15, Medium: 25, Hard: 40 };
const STORE_KEY = 'dsa-journal-revisions-v1';
const STEPS = [
  'Restate + clarify (size? range? sorted? dupes? empty?)',
  'Tiny example by hand + one edge case',
  'Name the brute force + its complexity',
  'Pattern-match out loud: "I see X, so it\'s Y"',
  'State the plan before coding',
  'Code it, narrating',
  'Dry-run on the example, then the edge case',
  'Final complexity + one extension'
];

const S = { cats: [], all: [], bySlug: {}, folders: {}, patterns: {}, repoRev: {}, cache: {}, meta: {},
  rev: { pattern: 'all', cur: null, start: null, acc: 0, running: false, rated: null } };

const $ = (s, r = document) => r.querySelector(s);
const $$ = (s, r = document) => [...r.querySelectorAll(s)];
const esc = s => String(s ?? '').replace(/[&<>"]/g, c => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]));
const slugify = t => t.toLowerCase().replace(/[^a-z0-9]+/g, '-').replace(/^-|-$/g, '');

/* ---------- dates ---------- */
const pad = n => String(n).padStart(2, '0');
const iso = d => `${d.getFullYear()}-${pad(d.getMonth() + 1)}-${pad(d.getDate())}`;
const todayISO = () => iso(new Date());
const fromISO = s => { const [y, m, d] = s.split('-').map(Number); return new Date(y, m - 1, d); };
const addDays = (s, n) => { const d = fromISO(s); d.setDate(d.getDate() + n); return iso(d); };
const daysUntil = s => Math.round((fromISO(s) - fromISO(todayISO())) / 864e5);
const fmtDate = s => fromISO(s).toLocaleDateString(undefined, { day: 'numeric', month: 'short' });
const fmtSecs = s => `${Math.floor(s / 60)}:${pad(Math.floor(s % 60))}`;

/* ---------- profiles ----------
   'owner' is the journal itself: solved flags from data/catalog.json, revisions from data/revisions.json + this browser.
   Every other profile lives only in this browser: { solved: {slug: date}, rev: {...}, days: {date: [slugs]} }. */
const isOwner = () => !S.user || S.user.id === 'owner';
function loadProfiles() { try { const o = JSON.parse(localStorage.getItem(PROFILES_KEY) || 'null'); return o && Array.isArray(o.list) ? o : null; } catch { return null; } }
function saveProfiles(o) { S.profiles = o; try { localStorage.setItem(PROFILES_KEY, JSON.stringify(o)); } catch {} }
const userKey = id => 'dsa-journal-user-' + id;
function udata() {
  if (!S.ud) { try { S.ud = JSON.parse(localStorage.getItem(userKey(S.user.id)) || '{}') || {}; } catch { S.ud = {}; } }
  S.ud.solved = S.ud.solved || {}; S.ud.rev = S.ud.rev || {}; S.ud.days = S.ud.days || {};
  return S.ud;
}
function saveUD() { try { localStorage.setItem(userKey(S.user.id), JSON.stringify(S.ud)); } catch {} }
function hasOwnerData() { try { return !!localStorage.getItem(STORE_KEY); } catch { return false; } }
// The journal's own data belongs to the user "Arnavjot". A browser shows it only after that name is entered
// with the passcode (checked against its SHA-256 here); everyone else only ever sees their own profile.
const OWNER_NAME = 'Arnavjot';
const OWNER_HASH = 'c6b36f04ad82f27184fe72d896e70580e1d7136fbfdb2213dabe40e2e2c1b18d';
const OWNER_FLAG = 'dsa-journal-is-owner';
async function sha256(t) { const b = await crypto.subtle.digest('SHA-256', new TextEncoder().encode(t)); return [...new Uint8Array(b)].map(x => x.toString(16).padStart(2, '0')).join(''); }
function isOwnerBrowser() { try { return localStorage.getItem(OWNER_FLAG) === '1'; } catch { return false; } }
function markOwnerBrowser() { try { localStorage.setItem(OWNER_FLAG, '1'); } catch {} }
// Switch to a profile: solved flags, revisions and the top bar all follow it.
function useProfile(id) {
  const prof = S.profiles || { active: 'owner', list: [] };
  if (id === 'owner' && !isOwnerBrowser()) return;               // the journal never opens without the passcode
  S.user = id === 'owner' ? { id: 'owner', name: OWNER_NAME } : prof.list.find(u => u.id === id) || null;
  if (!S.user) { S.user = { id: 'owner' }; saveProfiles({ ...prof, active: null }); S.all.forEach(p => { p.solved = false; }); drawProfileBtn(); return; }
  saveProfiles({ ...prof, active: S.user.id });
  S.ud = null; S.seeded = null; resetSession(); S.rev.pattern = 'all';
  const ud = isOwner() ? null : udata();
  S.all.forEach(p => { p.solved = ud ? !!ud.solved[p.slug] : p.baseSolved; });
  seedSchedule(); balanceSchedule();
  drawProfileBtn();
}

/* ---------- revision store (repo file as base, browser on top) ---------- */
function localRev() {
  if (!isOwner()) return JSON.parse(JSON.stringify(udata().rev));
  try { return JSON.parse(localStorage.getItem(STORE_KEY) || '{}') || {}; } catch { return {}; }
}
function saveLocal(obj) {
  if (!isOwner()) { udata().rev = obj; saveUD(); return; }
  try { localStorage.setItem(STORE_KEY, JSON.stringify(obj)); } catch {}
}
function allRev() {
  const out = isOwner() ? { ...(S.seeded || {}), ...S.repoRev } : {}, loc = localRev();
  for (const k in loc) if (!out[k] || (loc[k].updated || '') >= (out[k].updated || '')) out[k] = loc[k];
  return out;
}
function recOf(p) { return allRev()[p.slug] || { box: 0, due: todayISO(), log: [] }; }
function dueIn(p) { return daysUntil(recOf(p).due); }
function lastResult(p) { const l = recOf(p).log || []; return l.length ? l[l.length - 1].r : null; }
/* ---------- spreading reviews so no day piles up ---------- */
function dayLoad(skipSlug) {
  const n = {}, pats = {}, R = allRev();
  S.all.forEach(q => {
    const r = R[q.slug]; if (!q.solved || !r || q.slug === skipSlug) return;
    n[r.due] = (n[r.due] || 0) + 1;
    (pats[r.due] = pats[r.due] || new Set()).add(q.cat.slug);
  });
  return { n, pats };
}
// Best day within [lo, hi] days from today: under the daily cap, fewest problems,
// avoids a second problem from the same pattern, and stays close to the target gap.
function pickDay(p, target, lo, hi, load) {
  const today = todayISO();
  for (let extra = 0; extra <= 60; extra += 7) {
    let best = null, bestScore = Infinity;
    for (let o = lo; o <= hi + extra; o++) {
      const d = addDays(today, o), cnt = load.n[d] || 0;
      if (cnt >= DAILY_CAP) continue;                  // never more than DAILY_CAP reviews on one day
      const score = cnt * (cnt >= DAILY_CAP ? 3 : 1) + (load.pats[d] && load.pats[d].has(p.cat.slug) ? 2 : 0) + Math.abs(o - target) * 0.3;
      if (score < bestScore) { bestScore = score; best = d; }
    }
    if (best) return best;
  }
  return addDays(today, target);
}
function nextDue(p, gap, load) {
  const lo = Math.max(1, Math.round(gap * 0.85)), hi = Math.round(gap * 1.15) + (gap <= 3 ? 1 : 0);
  return pickDay(p, gap, lo, hi, load);
}
// Solved problems with no record yet get a first review date, a few per day, patterns mixed.
function seedSchedule() {
  const R = allRev();
  const groups = S.cats.map(c => c.problems.filter(p => p.solved && !R[p.slug])).filter(g => g.length);
  if (!groups.length) return;
  const order = [];
  for (let i = 0; groups.some(g => i < g.length); i++) groups.forEach(g => { if (i < g.length) order.push(g[i]); });
  const load = dayLoad(), loc = localRev(), today = todayISO();
  order.forEach(p => {
    let due = null;
    for (let o = 0; o < 400 && !due; o++) {
      const d = addDays(today, o), cnt = load.n[d] || 0;
      if (cnt < DAILY_CAP && !(load.pats[d] && load.pats[d].has(p.cat.slug) && cnt < order.length / DAILY_CAP)) due = d;
    }
    for (let o = 0; !due; o++) { const d = addDays(today, o); if ((load.n[d] || 0) < DAILY_CAP) due = d; }
    loc[p.slug] = { box: 0, due, log: [], updated: '0' };
    load.n[due] = (load.n[due] || 0) + 1;
    (load.pats[due] = load.pats[due] || new Set()).add(p.cat.slug);
  });
  saveLocal(loc);
  if (isOwner()) S.seeded = loc;
}
// Keep every day at DAILY_CAP reviews or fewer. Overdue problems count as today's; the most overdue
// (then the least practised) stay, the rest move to the next day with room. Runs on every load,
// so missed days never pile up into one long list.
function balanceSchedule() {
  const R = allRev(), today = todayISO();
  const items = S.all.filter(p => p.solved && R[p.slug]).map(p => ({ p, r: R[p.slug] }))
    .sort((a, b) => (a.r.due < b.r.due ? -1 : a.r.due > b.r.due ? 1 : 0) || (a.r.box || 0) - (b.r.box || 0));
  const n = {}, moved = {};
  items.forEach(({ p, r }) => {
    let d = r.due < today ? today : r.due;
    while ((n[d] || 0) >= DAILY_CAP) d = addDays(d, 1);
    n[d] = (n[d] || 0) + 1;
    if (d !== (r.due < today ? today : r.due)) moved[p.slug] = { ...r, due: d, updated: new Date().toISOString() };
  });
  if (!Object.keys(moved).length) return;
  const loc = localRev(); Object.assign(loc, moved); saveLocal(loc);
}

/* ---------- a profile's plan: NEW_PER_DAY new problems a day from its start date ---------- */
// Today's new problems are fixed the first time the day is opened: the first unsolved problems in
// NeetCode order, so anything left from earlier days comes first. Solving one today keeps it on today's list.
const planOrder = () => core().filter(p => !p.solved);
function planStarted() { return !isOwner() && S.user.start && daysUntil(S.user.start) <= 0; }
function planToday() {
  if (!planStarted()) return [];
  const ud = udata(), t = todayISO();
  if (!ud.days[t]) { ud.days[t] = planOrder().slice(0, NEW_PER_DAY).map(p => p.slug); saveUD(); }
  return ud.days[t].map(sl => S.bySlug[sl]).filter(Boolean);
}
const planDay = () => -daysUntil(S.user.start) + 1;
// Revisions for a day: solved problems due by then, most overdue first, at most DAILY_CAP.
function revisionsDue() { return S.all.filter(p => p.solved && dueIn(p) <= 0).sort((a, b) => dueIn(a) - dueIn(b) || (recOf(a).box || 0) - (recOf(b).box || 0)); }
// What the next days look like: new problems continue in order, revisions by their due dates.
function planAhead(nDays) {
  const today = planToday().map(p => p.slug), rest = planOrder().filter(p => !today.includes(p.slug)), R = allRev(), out = [];
  const startOff = planStarted() ? 1 : daysUntil(S.user.start);
  for (let i = 0; i < nDays; i++) {
    const off = startOff + i, d = addDays(todayISO(), off);
    const fresh = rest.slice(i * NEW_PER_DAY, (i + 1) * NEW_PER_DAY);
    const revs = S.all.filter(p => p.solved && R[p.slug] && R[p.slug].due === d);
    if (!fresh.length && !revs.length) continue;
    out.push({ d, off, fresh, revs });
  }
  return out;
}
// Mark a problem solved or not for the current (non-owner) profile. A newly solved problem gets its first review in 1–3 days.
function setSolved(p, on) {
  const ud = udata();
  if (on) {
    ud.solved[p.slug] = todayISO(); p.solved = true;
    if (!ud.rev[p.slug]) ud.rev[p.slug] = { box: 0, due: nextDue(p, 1, dayLoad(p.slug)), log: [], updated: new Date().toISOString() };
  } else { delete ud.solved[p.slug]; delete ud.rev[p.slug]; p.solved = false; }
  saveUD();
}

// date: the day the attempt happened (defaults to today; the manual log can pass an earlier day)
function rate(p, result, secs, date = todayISO()) {
  const r = JSON.parse(JSON.stringify(recOf(p)));
  if (result === 'fast') r.box = Math.min((r.box || 0) + 1, INTERVALS.length - 1);
  else if (result === 'fail') r.box = 0;
  else r.box = r.box || 0;
  const gap = result === 'fail' ? 1 : INTERVALS[r.box];
  const ago = -daysUntil(date);                          // how many days back the attempt was
  r.due = gap - ago > 0 ? nextDue(p, gap - ago, dayLoad(p.slug)) : todayISO();
  r.log = [...(r.log || []), { d: date, s: Math.round(secs), r: result }].sort((a, b) => a.d < b.d ? -1 : a.d > b.d ? 1 : 0);
  r.updated = new Date().toISOString();
  const loc = localRev(); loc[p.slug] = r; saveLocal(loc);
  return r;
}
function duePill(p) {
  if (!p.solved) return '';
  const d = dueIn(p);
  if (d <= 0) return `<span class="pill due">due${d < 0 ? ` · ${-d}d late` : ' today'}</span>`;
  return `<span class="pill soon">in ${d}d</span>`;
}

/* ---------- loading ---------- */
async function getJSON(u) { const r = await fetch(u, { cache: 'no-cache' }); if (!r.ok) throw new Error(u); return r.json(); }
async function getText(u) { if (S.cache[u] !== undefined) return S.cache[u]; const r = await fetch(u, { cache: 'no-cache' }); S.cache[u] = r.ok ? await r.text() : null; return S.cache[u]; }

async function boot() {
  try {
    const [cats, pats, folders, repoRev, daily] = await Promise.all([
      getJSON('data/catalog.json'), getJSON('data/patterns.json'),
      getJSON('problems/index.json').catch(() => []), getJSON('data/revisions.json').catch(() => ({})),
      getJSON('data/daily.json').catch(() => ({}))
    ]);
    S.cats = cats; S.patterns = pats; S.repoRev = repoRev || {}; S.daily = daily || {};
    folders.forEach(f => { const id = parseInt(f, 10); if (id) S.folders[id] = f; });
    cats.forEach(c => c.problems.forEach(p => {
      p.slug = slugify(p.title); p.cat = c; p.folder = S.folders[p.id] || null; p.baseSolved = !!p.solved;
      S.all.push(p); S.bySlug[p.slug] = p;
    }));
  } catch (e) {
    $('#view').innerHTML = `<div class="empty"><b>Couldn't load the data files.</b><br>Open this site through a web server (GitHub Pages, or run <code>npx serve .</code> in the repo folder), not by double-clicking index.html.</div>`;
    return;
  }
  // First visit: a browser that already holds the journal's revisions is the owner's; anyone else picks a profile.
  let prof = loadProfiles();
  if (!prof && isOwnerBrowser()) prof = { active: 'owner', list: [] };
  if (prof && prof.active === 'owner' && !isOwnerBrowser()) prof.active = null;
  S.profiles = prof || { active: null, list: [] };
  if (S.profiles.active) useProfile(S.profiles.active); else { S.user = { id: 'owner' }; S.all.forEach(p => { p.solved = false; }); drawProfileBtn(); }
  window.addEventListener('hashchange', route);
  route();
}

function route() {
  closeProfileMenu();
  const h = decodeURIComponent(location.hash.slice(1));
  if (!S.profiles.active && h !== 'welcome' && h !== 'new-profile') { location.replace('#welcome'); return; }
  $$('.top nav a').forEach(a => a.classList.toggle('on', a.dataset.nav === (['revise', 'history'].includes(h) ? h : (h ? '' : 'home'))));
  // from a visualizer's top bar: #info opens the info box, #profile opens the profile menu, on the home page
  if (h === 'info' || h === 'profile') {
    history.replaceState(null, '', location.pathname); renderHome();
    if (h === 'info') { const d = $('#info'); if (d.showModal) d.showModal(); else d.setAttribute('open', ''); }
    else setTimeout(openProfileMenu, 0);
    return;
  }
  if (h === 'welcome') renderWelcome();
  else if (h === 'new-profile') renderNewProfile();
  else if (h === 'revise') renderRevise();
  else if (h === 'history') renderHistory();
  else if (S.bySlug[h]) { S.lastSlug = h; renderProblem(S.bySlug[h]); }
  else { renderHome(); if (scrollToLast()) return; }
  window.scrollTo(0, 0);
}
// Back on the home page: show the problem you just left, inside its (open) pattern.
function scrollToLast() {
  const a = S.lastSlug && $(`.plist a[href="#${CSS.escape(S.lastSlug)}"]`);
  if (!a) return false;
  a.scrollIntoView({ block: 'center' });
  a.classList.add('last');
  return true;
}

/* ---------- home ---------- */
const core = () => S.all.filter(p => !p.cat.extra);
function catStats(c) {
  const sol = c.problems.filter(p => p.solved);
  return { solved: sol.length, total: c.problems.length, due: sol.filter(p => dueIn(p) <= 0).length,
    weak: sol.filter(p => lastResult(p) === 'fail').length };
}

function renderHome() {
  const cs = core(), solved = cs.filter(p => p.solved);
  const by = d => solved.filter(p => p.difficulty === d).length;
  const tot = d => cs.filter(p => p.difficulty === d).length;
  const dueAll = S.all.filter(p => p.solved && dueIn(p) <= 0), dueShown = isOwner() ? dueAll.length : Math.min(dueAll.length, DAILY_CAP);
  const pct = n => (100 * n / cs.length).toFixed(2);
  $('#view').innerHTML = `
    <section class="hero">
      <div class="card">
        <div class="label">NeetCode 150</div>
        <div class="big" style="margin:8px 0 12px">${solved.length}<small> / ${cs.length} solved</small></div>
        <div class="bar"><i style="width:${pct(by('Easy'))}%;background:var(--easy)"></i><i style="width:${pct(by('Medium'))}%;background:var(--med-bar)"></i><i style="width:${pct(by('Hard'))}%;background:var(--hard)"></i></div>
        <div class="split"><span><b>${by('Easy')}</b>/${tot('Easy')} Easy</span><span><b>${by('Medium')}</b>/${tot('Medium')} Medium</span><span><b>${by('Hard')}</b>/${tot('Hard')} Hard</span><span><b>${Object.keys(S.folders).length}</b> with full notes</span></div>
      </div>
      <div class="card due-card">
        <div><div class="label">Due for revision</div>
        <div class="big" style="margin-top:8px">${dueShown}<small> problem${dueShown === 1 ? '' : 's'}${isOwner() ? '' : ' today'}</small></div></div>
        <div class="muted" style="font-size:14px">${isOwner() ? 'Pick a pattern and re-solve one under a timer, running the 8 steps.' : `At most ${DAILY_CAP} a day.${dueAll.length > DAILY_CAP ? ` ${dueAll.length - DAILY_CAP} more are waiting and come up next.` : ''} Re-solve each under a timer, running the 8 steps.`}</div>
        <div><a class="btn primary" href="#revise">Start timed revision →</a></div>
      </div>
    </section>
    ${isOwner() ? dailyCard() : todayCard()}
    <section style="display:flex;flex-direction:column;gap:12px">
      <div style="display:flex;align-items:baseline;gap:12px;flex-wrap:wrap"><h2>Patterns</h2><span class="muted" style="font-size:14px">Tap a pattern to see its problems.${isOwner() ? '' : ' Solved one? Tap its circle.'} Red border = you failed one there recently.</span></div>
      <div class="cats">${S.cats.map(catCard).join('')}</div>
    </section>`;
}

// Daily problems (data/daily.json: { "YYYY-MM-DD": [ids] }). Shows today's list, or the next upcoming day.
function dailyCard() {
  const days = Object.keys(S.daily || {}).sort();
  const day = days.includes(todayISO()) ? todayISO() : days.find(d => d > todayISO());
  if (!day) return '';
  const byId = Object.fromEntries(S.all.map(p => [p.id, p]));
  const list = (S.daily[day] || []).map(id => byId[id]).filter(Boolean);
  const d = daysUntil(day), when = d === 0 ? 'Today' : d === 1 ? 'Tomorrow' : `In ${d} days`;
  const done = list.filter(p => p.solved).length;
  return `<section class="card daily">
    <div class="daily-head"><div><div class="label">Daily problems</div><h2 style="margin-top:4px">${when} · ${fmtDate(day)}</h2></div>
      <span class="pill ${done === list.length ? 'ok' : 'soon'}">${done}/${list.length} done</span></div>
    <ul class="plist daily-list">${list.map(p => `<li class="${p.solved ? '' : 'todo'}"><a href="#${p.slug}">
      <span class="dot${p.solved ? ' on' : ''}"></span><span class="num">#${p.id}</span><span class="t">${esc(p.title)}</span>
      <span class="meta"><span class="pill soon">${esc(p.cat.name)}</span><span class="diff ${p.difficulty}">${p.difficulty[0]}</span></span></a></li>`).join('')}</ul>
  </section>`;
}

function catCard(c) {
  const st = catStats(c), pat = S.patterns[c.slug] || {};
  const last = S.lastSlug && S.bySlug[S.lastSlug];
  const open = last && last.cat === c ? ' open' : '';     // only the pattern you came back from
  const badge = st.weak ? `<span class="pill weak">${st.weak} weak</span>` : st.due ? `<span class="pill due">${st.due} due</span>` : st.solved ? `<span class="pill ok">up to date</span>` : '';
  return `<details class="cat${st.weak ? ' weak' : ''}"${open}>
    <summary>
      <div class="cat-head"><span class="chev">▸</span><h3>${esc(c.name)}</h3>${badge}<span class="cat-count">${st.solved}/${st.total}</span></div>
      <div class="bar" style="height:6px"><i style="width:${100 * st.solved / st.total}%;background:var(--accent)"></i></div>
      ${pat.spot ? `<div class="spot"><b>Spot it:</b> ${esc(pat.spot)}</div>` : ''}
    </summary>
    <ul class="plist">${c.problems.map(p => `<li class="${p.solved ? '' : 'todo'}"><a href="#${p.slug}">
      ${dotHTML(p, p.solved)}
      <span class="num">#${p.id}</span>
      <span class="t">${esc(p.title)}</span>
      <span class="meta">${p.folder ? '<span class="pill notes">notes</span>' : ''}${duePill(p)}<span class="diff ${p.difficulty}">${p.difficulty[0]}</span></span>
    </a></li>`).join('')}</ul>
  </details>`;
}

/* ---------- problem page ---------- */
// Display only: drop blank lines that just add space (doubled, right after "{" or ":", right before "}", at the ends).
// Copy still gives the file exactly as written.
function tidyCode(t) {
  if (!t) return t;
  const L = t.replace(/\r/g, '').split('\n'), out = [];
  L.forEach((l, i) => {
    if (l.trim()) { out.push(l); return; }
    const prev = out.length ? out[out.length - 1] : null;
    let n = i + 1; while (n < L.length && !L[n].trim()) n++;
    if (prev === null || !prev.trim() || /[{:]$/.test(prev.trim()) || n >= L.length || /^}/.test(L[n].trim())) return;
    out.push('');
  });
  return out.join('\n');
}
async function renderProblem(p) {
  const v = $('#view');
  const lc = `https://leetcode.com/problems/${p.slug}/`;
  const rec = recOf(p);
  const head = `
    <div class="phead"><a class="crumb" href="#"><span class="arr" aria-hidden="true">←</span>${esc(p.cat.name)}</a>${isOwner() ? '' : p.solved ? '<button class="btn solved-btn" id="unmark" title="Tap to unmark">✓ Solved</button>' : '<button class="btn primary" id="markSolved">✓ Mark solved</button>'}</div>
    <div class="ptitle">
      <h1><span class="muted" style="font-family:var(--f-mono);font-weight:600">#${p.id}</span> ${esc(p.title)}</h1>
      <div class="row"><span class="diff ${p.difficulty}">${p.difficulty}</span>
        <span class="pill soon">${esc(p.cat.name)}</span>
        ${p.solved ? '<span class="pill ok">solved</span>' : '<span class="pill soon">not solved yet</span>'}
        ${duePill(p)}
        <a class="btn sm" href="${lc}" target="_blank" rel="noopener">Open on LeetCode ↗</a></div>
    </div>`;
  const revCard = p.solved ? `
    <div class="card revbox">
      <div style="flex:1;min-width:200px"><div class="label">Revision</div>
        <div style="font-size:14px">Next review <b>${fmtDate(rec.due)}</b> · ${(rec.log || []).length} attempt${(rec.log || []).length === 1 ? '' : 's'} logged${(rec.log || []).length ? ` · last: ${resultLabel(rec.log[rec.log.length - 1].r)} in ${fmtSecs(rec.log[rec.log.length - 1].s)}` : ''}</div></div>
      <div style="display:flex;gap:8px;flex-wrap:wrap"><button class="btn" id="logOpen">Log an attempt</button><button class="btn primary" id="reviseThis">Re-solve with timer</button></div>
      <form class="logform" id="logForm" hidden>
        <label>Date <input type="date" id="logDate" value="${todayISO()}" max="${todayISO()}" required></label>
        <label>Time <span class="mmss"><input type="number" id="logMin" min="0" max="300" placeholder="10" required aria-label="Minutes"> min <input type="number" id="logSec" min="0" max="59" placeholder="0" aria-label="Seconds"> s</span></label>
        <label>Result <select id="logRes"><option value="fast">Solved in time</option><option value="slow">Solved, but slow</option><option value="fail">Couldn't solve</option></select></label>
        <button class="btn primary" type="submit">Save</button>
        <span class="muted" style="font-size:13px">${isOwner() ? 'Saved in this browser. Use History → Copy to keep it on GitHub.' : 'Saved in this browser. Use History → Export to move it to another device.'}</span>
      </form>
    </div>` : '';
  const nav = pnav(p);

  if (!p.folder) {
    v.innerHTML = `${head}${revCard}
      <div class="empty"><b>Notes not written yet.</b>${isOwner() ? `<br>Copy <code>problems/_template</code> to <code>problems/${p.id}-${p.slug}</code>, fill in the 8 steps and your code, then push.` : '<br>Solve it on LeetCode, then mark it solved here so it joins your revisions.'}</div>${nav}`;
    bindReviseThis(p);
    return;
  }

  v.innerHTML = `${head}<p class="muted">Loading notes…</p>`;
  const base = `problems/${p.folder}/`;
  let meta;
  try { meta = await getJSON(base + 'meta.json'); } catch { v.innerHTML = `${head}<div class="empty">meta.json is missing or has a typo.</div>`; return; }
  const [notes, ...codes] = await Promise.all([getText(base + 'notes.md'), ...meta.approaches.map(a => getText(base + a.file))]);
  if (location.hash.slice(1) !== p.slug) return;

  const tabs = meta.approaches.map((a, i) => `<button class="tab" role="tab" data-ap="${i}" aria-selected="${i === meta.approaches.length - 1}">
      <span class="n">${esc(a.name)}</span><span class="c">${esc(a.time)} time · ${esc(a.space)} space</span>${a.best ? '<span class="star">★ optimal</span>' : ''}</button>`).join('');
  const panes = meta.approaches.map((a, i) => `<div class="appr" data-pane="${i}" ${i === meta.approaches.length - 1 ? '' : 'hidden'}>
      <div>${esc(a.idea)}</div>
      ${a.warn ? `<div class="warn">${esc(a.warn)}</div>` : ''}
      <div class="cx"><span class="label">Time</span><span class="cxv">${esc(a.time)}</span><span class="label">Space</span><span class="cxv">${esc(a.space)}</span>
        <button class="ibtn" data-why="${i}" aria-expanded="false" title="Why this complexity?">i</button></div>
      <div class="why" data-whyp="${i}" hidden>${esc(a.why || '')}</div>
      ${a.viz ? `<div class="vizcta" id="vizcta-${i}">
        <div class="vizcta-text"><b>Step-by-step visualizer</b><span>Pointers move on the picture while the code highlights line by line.</span></div>
        <div class="vizcta-btns"><a class="btn primary" href="${esc(a.viz)}">▶ Open visualizer</a></div>
      </div>` : ''}
      <div class="codebox"><button class="btn sm copy" data-copy="${i}">Copy</button><pre><code class="language-cpp">${esc(tidyCode(codes[i]) || '// file missing: ' + a.file)}</code></pre></div>
    </div>`).join('');

  let html = notes ? (window.marked ? marked.parse(notes) : `<pre>${esc(notes)}</pre>`) : '';
  const tmp = document.createElement('div'); tmp.innerHTML = html;
  const heads = $$('h2', tmp); heads.forEach((h, i) => h.id = 'step-' + i);
  html = tmp.innerHTML;

  v.innerHTML = `${head}
    <div class="key">${esc(meta.keyIdea || '')}</div>
    ${revCard}
    <section class="card" style="display:flex;flex-direction:column;gap:14px">
      <div class="label">Approaches</div>
      <div class="tabs" role="tablist">${tabs}</div>
      ${panes}
    </section>
    ${notes ? `<section class="card" style="display:flex;flex-direction:column;gap:12px">
      <div class="label">The 8 steps</div>
      <div class="stepnav">${heads.map((h, i) => `<a href="#${p.slug}" data-jump="step-${i}">${esc(h.textContent)}</a>`).join('')}</div>
      <div class="md">${html}</div></section>` : ''}
    ${meta.quiz && meta.quiz.length ? `<section class="card quiz"><div class="label">Quick check</div>${meta.quiz.map((q, qi) => `
      <div class="qq"><p>${qi + 1}. ${esc(q.q)}</p>${q.options.map((o, oi) => `<button class="opt" data-q="${qi}" data-o="${oi}">${esc(o)}</button>`).join('')}</div>`).join('')}</section>` : ''}
    ${nav}`;

  if (window.hljs) $$('pre code', v).forEach(el => { try { hljs.highlightElement(el); } catch {} });
  $$('[data-ap]', v).forEach(b => b.onclick = () => {
    $$('[data-ap]', v).forEach(x => x.setAttribute('aria-selected', x === b));
    $$('[data-pane]', v).forEach(x => x.hidden = x.dataset.pane !== b.dataset.ap);
  });
  $$('[data-why]', v).forEach(b => b.onclick = () => {
    const pane = $(`[data-whyp="${b.dataset.why}"]`, v); pane.hidden = !pane.hidden; b.setAttribute('aria-expanded', !pane.hidden);
  });
  $$('[data-copy]', v).forEach(b => b.onclick = async () => {
    const txt = codes[+b.dataset.copy] || '';
    try { await navigator.clipboard.writeText(txt); b.textContent = 'Copied'; }
    catch { const r = document.createRange(); r.selectNodeContents(b.nextElementSibling); const s = getSelection(); s.removeAllRanges(); s.addRange(r); b.textContent = 'Selected'; }
    setTimeout(() => b.textContent = 'Copy', 1500);
  });
  $$('[data-jump]', v).forEach(a => a.onclick = e => { e.preventDefault(); document.getElementById(a.dataset.jump)?.scrollIntoView({ behavior: 'smooth' }); });
  $$('.opt', v).forEach(b => b.onclick = () => {
    const q = meta.quiz[+b.dataset.q], right = +b.dataset.o === q.answer;
    b.classList.add(right ? 'right' : 'wrong');
    if (!right) $(`.opt[data-q="${b.dataset.q}"][data-o="${q.answer}"]`, v).classList.add('right');
  });
  bindReviseThis(p);
}

function pnav(p) {
  const list = p.cat.problems, i = list.indexOf(p);
  const a = list[i - 1], b = list[i + 1];
  return `<div class="pnav">${a ? `<a class="btn" href="#${a.slug}">← ${esc(a.title)}</a>` : '<span></span>'}${b ? `<a class="btn" href="#${b.slug}">${esc(b.title)} →</a>` : ''}</div>`;
}
function bindLogForm(p) {
  const open = $('#logOpen'), form = $('#logForm');
  if (!open || !form) return;
  open.onclick = () => { form.hidden = !form.hidden; };
  form.onsubmit = e => {
    e.preventDefault();
    const date = $('#logDate').value, secs = (+$('#logMin').value || 0) * 60 + (+$('#logSec').value || 0);
    if (!date || date > todayISO()) return;
    rate(p, $('#logRes').value, secs, date);
    renderProblem(p);
  };
}
function bindReviseThis(p) {
  bindLogForm(p);
  const ms = $('#markSolved'); if (ms) ms.onclick = () => { setSolved(p, true); renderProblem(p); };
  const um = $('#unmark'); if (um) um.onclick = () => {
    const n = (recOf(p).log || []).length;
    if (n && !confirm(`Unmark #${p.id}? Its ${n} logged attempt${n === 1 ? '' : 's'} will be removed too.`)) return;
    setSolved(p, false); renderProblem(p);
  };
  const b = $('#reviseThis'); if (!b) return;
  b.onclick = () => { resetSession(); S.rev.cur = p; location.hash = 'revise'; };
}
const resultLabel = r => ({ fast: 'in time', slow: 'slow', fail: "couldn't" }[r] || r);

/* ---------- revise ---------- */
function resetSession() { stopTimer(); Object.assign(S.rev, { cur: null, start: null, acc: 0, running: false, rated: null }); }
function pool(pattern) { return S.all.filter(p => p.solved && (pattern === 'all' || p.cat.slug === pattern)); }
function pickNext(pattern) { return pool(pattern).sort((a, b) => dueIn(a) - dueIn(b) || (recOf(a).box || 0) - (recOf(b).box || 0))[0] || null; }
const elapsed = () => S.rev.acc + (S.rev.running ? (Date.now() - S.rev.start) / 1000 : 0);
let tick = null;
function startTimer() { if (S.rev.running) return; S.rev.start = Date.now(); S.rev.running = true; tick = setInterval(drawTimer, 500); drawTimer(); }
function pauseTimer() { if (!S.rev.running) return; S.rev.acc = elapsed(); S.rev.running = false; clearInterval(tick); drawTimer(); }
function stopTimer() { clearInterval(tick); S.rev.running = false; }
function drawTimer() {
  const el = $('#timer'); if (!el || !S.rev.cur) return;
  const lim = LIMIT_MIN[S.rev.cur.difficulty] * 60, e = elapsed(), left = lim - e;
  el.textContent = left >= 0 ? fmtSecs(left) : '+' + fmtSecs(-left);
  el.classList.toggle('over', left < 0);
  const bar = $('#tbar'); if (bar) bar.style.width = Math.min(100, 100 * e / lim) + '%';
  const tb = $('#tbtn'); if (tb) tb.textContent = S.rev.running ? '❚❚ Pause' : (e > 0 ? '▶ Resume' : '▶ Start timer');
}

// The 8-step checklist. With a problem's own prompts (meta.json "steps"), each step gets a targeted question under it.
function stepItems(prompts) {
  return STEPS.map((s, i) => `<li><label><input type="checkbox" id="st${i}"><span><b>${i + 1}. ${esc(s)}</b>` +
    (prompts && prompts[i] ? `<small class="prompt">${esc(prompts[i])}</small>` : '') + `</span></label></li>`).join('');
}
async function loadTargetedSteps(p) {
  if (!p || !p.folder) return;
  let meta;
  try { meta = S.meta[p.folder] || (S.meta[p.folder] = await getJSON(`problems/${p.folder}/meta.json`)); } catch { return; }
  const ul = $('#steps');
  if (!ul || S.rev.cur !== p || !Array.isArray(meta.steps) || meta.steps.length !== STEPS.length) return;
  ul.innerHTML = stepItems(meta.steps);
  $('#stepsLabel').textContent = `Run the 8 steps out loud · for #${p.id}`;
}

function renderRevise() {
  const pats = S.cats.filter(c => c.problems.some(p => p.solved));
  const dueCount = slug => pool(slug).filter(p => dueIn(p) <= 0).length;
  const chips = [{ slug: 'all', name: 'Most overdue anywhere' }, ...pats].map(c => {
    const n = dueCount(c.slug);
    return `<button class="chip" data-pat="${c.slug}" aria-pressed="${S.rev.pattern === c.slug}">${esc(c.name)}<span class="c${n ? '' : ' z'}">${n}</span></button>`;
  }).join('');
  if (!S.rev.cur) S.rev.cur = pickNext(S.rev.pattern);
  const p = S.rev.cur;
  let body;
  if (!p) body = `<div class="empty">No solved problems in this pattern yet.</div>`;
  else if (S.rev.rated) {
    const r = recOf(p);
    body = `<div class="card" style="display:flex;flex-direction:column;gap:12px">
      <div class="label">Logged</div>
      <h2>#${p.id} ${esc(p.title)}: ${resultLabel(S.rev.rated)} in ${fmtSecs(r.log[r.log.length - 1].s)}</h2>
      <div class="muted">Next review: <b style="color:var(--ink)">${fmtDate(r.due)}</b> (in ${daysUntil(r.due)} day${daysUntil(r.due) === 1 ? '' : 's'}).</div>
      <div style="display:flex;gap:8px;flex-wrap:wrap"><button class="btn primary" id="nextP">Next problem →</button><a class="btn" href="#${p.slug}">Compare with my notes</a></div>
    </div>`;
  } else {
    const d = dueIn(p), lim = LIMIT_MIN[p.difficulty];
    body = `<div class="session">
      <div class="card" style="display:flex;flex-direction:column;gap:14px">
        <div class="label">${esc(p.cat.name)} · ${d <= 0 ? (d < 0 ? `${-d} days overdue` : 'due today') : `not due for ${d} days`}</div>
        <h2 style="font-size:24px">#${p.id} ${esc(p.title)} <span class="diff ${p.difficulty}">${p.difficulty}</span></h2>
        <div><a class="btn" href="https://leetcode.com/problems/${p.slug}/" target="_blank" rel="noopener">Open on LeetCode ↗</a></div>
        <div><div id="timer" class="timer">${lim}:00</div><div class="tbar" style="margin-top:10px"><i id="tbar" style="width:0"></i></div>
        <div class="muted" style="font-size:13px;margin-top:6px">${lim}-minute target for ${p.difficulty}. Don't open your notes until you rate.</div></div>
        <div style="display:flex;gap:8px;flex-wrap:wrap"><button class="btn primary" id="tbtn">▶ Start timer</button><button class="btn" id="skip">Skip this one</button></div>
        <div><div class="label" style="margin-bottom:8px">How did it go?</div>
        <div class="rate">
          <button class="r-fast" data-rate="fast"><b>Solved in time</b><span>Next gap gets longer</span></button>
          <button class="r-slow" data-rate="slow"><b>Solved, but slow</b><span>Same gap again</span></button>
          <button class="r-fail" data-rate="fail"><b>Couldn't solve</b><span>Back to tomorrow</span></button>
        </div></div>
        <form class="logform revlog" id="revLog">
          <div class="label" style="flex-basis:100%">Didn't use the timer? Log your time</div>
          <label>Time <span class="mmss"><input type="number" id="rlMin" min="0" max="300" placeholder="10" required aria-label="Minutes"> min <input type="number" id="rlSec" min="0" max="59" placeholder="0" aria-label="Seconds"> s</span></label>
          <label>Result <select id="rlRes"><option value="fast">Solved in time</option><option value="slow">Solved, but slow</option><option value="fail">Couldn't solve</option></select></label>
          <button class="btn primary" type="submit">Log</button>
        </form>
      </div>
      <div class="card"><div class="label" style="margin-bottom:8px" id="stepsLabel">Run the 8 steps out loud</div>
        <ul class="checklist" id="steps">${stepItems()}</ul>
        <p class="muted" style="font-size:13px;margin:10px 0 0">Stuck? Tap the <b>i</b> button at the top for the never-stuck questions.</p>
      </div>
    </div>`;
  }
  $('#view').innerHTML = `
    <div><h1>Timed revision</h1><p class="muted" style="margin:6px 0 0">Choose a pattern. You get its most overdue problem with only the title showing. Solve it on LeetCode against the clock, then rate yourself.</p></div>
    <div class="chips">${chips}</div>
    ${body}
    <div class="card"><div class="label" style="margin-bottom:6px">How the schedule works</div>
      <div class="muted" style="font-size:14px">Each problem has a gap of ${INTERVALS.join(' → ')} days. Solved in time moves it one step longer, slow keeps the same gap, couldn't brings it back in 1–2 days. No more than ${DAILY_CAP} problems are scheduled on one day: the next date can shift a little either side of the gap to a quieter day, and problems from the same pattern are kept on different days. A pattern turns red on the home page when its last attempt failed.</div></div>`;

  loadTargetedSteps(p);
  $$('[data-pat]').forEach(b => b.onclick = () => { S.rev.pattern = b.dataset.pat; resetSession(); renderRevise(); });
  const tb = $('#tbtn'); if (tb) tb.onclick = () => S.rev.running ? pauseTimer() : startTimer();
  const sk = $('#skip'); if (sk) sk.onclick = () => {
    const list = pool(S.rev.pattern).sort((a, b) => dueIn(a) - dueIn(b));
    const nxt = list[(list.indexOf(S.rev.cur) + 1) % list.length]; resetSession(); S.rev.cur = nxt; renderRevise();
  };
  $$('[data-rate]').forEach(b => b.onclick = () => { const secs = elapsed(); stopTimer(); rate(S.rev.cur, b.dataset.rate, secs); S.rev.rated = b.dataset.rate; renderRevise(); });
  const rl = $('#revLog');
  if (rl) {
    // typing a time picks the matching result: within the target = in time, over it = slow
    const lim = LIMIT_MIN[S.rev.cur.difficulty] * 60;
    const guess = () => { const t = (+$('#rlMin').value || 0) * 60 + (+$('#rlSec').value || 0); if ($('#rlRes').value !== 'fail') $('#rlRes').value = t <= lim ? 'fast' : 'slow'; };
    $('#rlMin').oninput = guess; $('#rlSec').oninput = guess;
    rl.onsubmit = e => {
      e.preventDefault();
      const secs = (+$('#rlMin').value || 0) * 60 + (+$('#rlSec').value || 0), res = $('#rlRes').value;
      stopTimer(); rate(S.rev.cur, res, secs); S.rev.rated = res; renderRevise();
    };
  }
  const np = $('#nextP'); if (np) np.onclick = () => { resetSession(); renderRevise(); };
  drawTimer();
}

/* ---------- history ---------- */
function renderHistory() {
  const rev = allRev(), rows = [];
  S.all.forEach(p => (rev[p.slug]?.log || []).forEach(l => rows.push({ p, ...l })));
  rows.sort((a, b) => b.d.localeCompare(a.d));
  const perCat = S.cats.map(c => {
    const r = rows.filter(x => x.p.cat === c);
    return r.length ? { c, n: r.length, avg: r.reduce((s, x) => s + x.s, 0) / r.length, fails: r.filter(x => x.r === 'fail').length } : null;
  }).filter(Boolean);
  $('#view').innerHTML = `
    <div><h1>History</h1><p class="muted" style="margin:6px 0 0">Every timed attempt. Watch your times drop.</p></div>
    ${perCat.length ? `<div class="card"><div class="label" style="margin-bottom:8px">By pattern</div><div class="tscroll"><table class="log">
      <thead><tr><th>Pattern</th><th>Attempts</th><th>Avg time</th><th>Couldn't</th></tr></thead>
      <tbody>${perCat.map(x => `<tr><td>${esc(x.c.name)}</td><td class="n">${x.n}</td><td class="n">${fmtSecs(x.avg)}</td><td class="n">${x.fails}</td></tr>`).join('')}</tbody></table></div></div>` : ''}
    <div class="card"><div class="label" style="margin-bottom:8px">All attempts</div>
      ${rows.length ? `<div class="tscroll"><table class="log"><thead><tr><th>Date</th><th>Problem</th><th>Time</th><th>Result</th></tr></thead><tbody>
      ${rows.map(x => `<tr><td class="n">${fmtDate(x.d)}</td><td><a href="#${x.p.slug}">#${x.p.id} ${esc(x.p.title)}</a></td><td class="n">${fmtSecs(x.s)}</td><td>${resultLabel(x.r)}</td></tr>`).join('')}
      </tbody></table></div>` : `<div class="empty">No attempts yet. <a href="#revise">Start a timed revision</a>.</div>`}</div>
    ${isOwner() ? `<div class="card" style="display:flex;flex-direction:column;gap:10px">
      <div class="label">Sync between devices</div>
      <div class="muted" style="font-size:14px">Your revisions save in this browser. To keep them on GitHub (and on your phone), copy this, paste it into <code>data/revisions.json</code> in the repo, and push. To load revisions here, paste JSON and press Import.</div>
      <textarea class="io" id="io" spellcheck="false">${esc(JSON.stringify(rev, null, 1))}</textarea>
      <div style="display:flex;gap:8px;flex-wrap:wrap"><button class="btn primary" id="cp">Copy</button><button class="btn" id="im">Import pasted JSON</button><span id="iomsg" class="muted" style="font-size:13px;align-self:center"></span></div>
    </div>` : progressBox()}`;
  if (!isOwner()) { bindProgressBox(); return; }
  $('#cp').onclick = async () => {
    try { await navigator.clipboard.writeText($('#io').value); $('#iomsg').textContent = 'Copied.'; }
    catch { $('#io').select(); $('#iomsg').textContent = 'Selected. Press Ctrl/Cmd + C.'; }
  };
  $('#im').onclick = () => {
    try { const o = JSON.parse($('#io').value); if (typeof o !== 'object' || Array.isArray(o)) throw 0; saveLocal(o); $('#iomsg').textContent = 'Imported.'; renderHistory(); }
    catch { $('#iomsg').textContent = "That isn't valid revisions JSON. Copy it again from the other device."; }
  };
}

/* ---------- profile button + menu (top bar) ---------- */
// a profile started without a name is called "User" and shows the person icon instead of a letter
const unnamed = u => !u || !u.name || u.name === 'User';
const initial = u => (unnamed(u) ? '' : u.name.trim()[0]).toUpperCase();
const avatar = u => initial(u) ? esc(initial(u)) : PERSON;
const PERSON = '<svg viewBox="0 0 24 24" width="18" height="18" aria-hidden="true"><circle cx="12" cy="8.5" r="4" fill="currentColor"/><path d="M4 20.5c.8-4.2 4-6.5 8-6.5s7.2 2.3 8 6.5" fill="currentColor"/></svg>';
function drawProfileBtn() {
  const b = $('#profBtn'); if (!b) return;
  const signed = S.profiles && S.profiles.active;
  b.innerHTML = signed ? avatar(S.user) : PERSON;
  b.classList.toggle('me', !!signed);
  b.title = signed ? `Profile: ${S.user.name}` : 'Profiles';
  b.setAttribute('aria-label', b.title);
  const np = $('#navPlan'); if (np) np.hidden = isOwner();
}
function closeProfileMenu() { const m = $('#profMenu'); if (m) m.hidden = true; const b = $('#profBtn'); if (b) b.setAttribute('aria-expanded', 'false'); }
function openProfileMenu() {
  const m = $('#profMenu'), list = (S.profiles && S.profiles.list) || [];
  m.innerHTML = `${list.map(u => `<button class="pm-item${S.user.id === u.id ? ' on' : ''}" data-prof="${esc(u.id)}"><span class="av">${avatar(u)}</span><span>${esc(u.name)}</span>${S.user.id === u.id ? '<span class="pm-tick">✓</span>' : ''}</button>`).join('')}
    ${isOwnerBrowser() ? `<button class="pm-item${isOwner() && S.profiles.active ? ' on' : ''}" data-prof="owner"><span class="av">${esc(OWNER_NAME[0])}</span><span>${esc(OWNER_NAME)}</span>${isOwner() && S.profiles.active ? '<span class="pm-tick">✓</span>' : ''}</button>` : ''}
    <a class="pm-item" href="#new-profile"><span class="av plus">+</span><span>New profile</span></a>
    ${isOwner() ? '' : `    <button class="pm-item danger" id="pmDel"><span class="av plus">×</span><span>Delete this profile</span></button>`}`;
  m.hidden = false; $('#profBtn').setAttribute('aria-expanded', 'true');
  $$('[data-prof]', m).forEach(x => x.onclick = () => { closeProfileMenu(); useProfile(x.dataset.prof); if (location.hash && location.hash !== '#') location.hash = ''; else route(); });
  const del = $('#pmDel', m); if (del) del.onclick = () => {
    if (!confirm(`Delete the profile "${S.user.name}" and all its progress in this browser? Export it from History first if you want a copy.`)) return;
    try { localStorage.removeItem(userKey(S.user.id)); } catch {}
    const rest = S.profiles.list.filter(u => u.id !== S.user.id);
    const next = rest.length ? rest[0].id : isOwnerBrowser() ? 'owner' : null;
    saveProfiles({ active: next, list: rest });
    closeProfileMenu();
    if (next) { useProfile(next); location.hash = ''; } else { S.user = { id: 'owner' }; S.all.forEach(p => { p.solved = false; }); drawProfileBtn(); location.hash = 'welcome'; }
  };
}
$('#profBtn').onclick = e => { e.stopPropagation(); $('#profMenu').hidden ? openProfileMenu() : closeProfileMenu(); };
document.addEventListener('click', e => { if (!e.target.closest('#profMenu')) closeProfileMenu(); });
document.addEventListener('keydown', e => { if (e.key === 'Escape') closeProfileMenu(); });

/* ---------- welcome + new profile ---------- */
function renderWelcome() {
  $('#view').innerHTML = `
    <section class="welcome card">
      <div class="label">Welcome</div>
      <h1>Who's using this?</h1>
      <p class="muted" style="margin:0">Make your profile: you get ${NEW_PER_DAY} new NeetCode 150 problems a day from your start date, and at most ${DAILY_CAP} revisions a day on a spaced schedule. Every visualizer and note is here for you. Your progress stays in this browser.</p>
      <div class="welcome-btns">
        <a class="btn primary" href="#new-profile">Start my plan →</a>
        ${(S.profiles.list || []).map(u => `<button class="btn" data-pick="${esc(u.id)}"><span class="av sm">${avatar(u)}</span>${esc(u.name)}</button>`).join('')}
        ${isOwnerBrowser() ? `<button class="btn" data-pick="owner"><span class="av sm">${esc(OWNER_NAME[0])}</span>${esc(OWNER_NAME)}</button>` : ''}
      </div>
      <details class="welcome-imp"><summary>Moving from another device? Import your progress</summary>
        <p class="muted" style="font-size:14px;margin:8px 0">On the other device, open History and press Export. Paste it here.</p>
        <textarea class="io" id="wio" spellcheck="false" placeholder='{"name": …}'></textarea>
        <div style="display:flex;gap:8px;align-items:center;margin-top:8px"><button class="btn primary" id="wimp">Import</button><span id="wmsg" class="muted" style="font-size:13px"></span></div>
      </details>
    </section>`;
  $$('[data-pick]').forEach(b => b.onclick = () => { useProfile(b.dataset.pick); location.hash = ''; });
  $('#wimp').onclick = () => {
    const o = parseProgress($('#wio').value);
    if (!o) { $('#wmsg').textContent = "That isn't an exported progress file. Export it again on the other device."; return; }
    const id = Date.now().toString(36);
    saveProfiles({ active: id, list: [...(S.profiles.list || []), { id, name: o.name, start: o.start }] });
    try { localStorage.setItem(userKey(id), JSON.stringify({ solved: o.solved, rev: o.rev, days: o.days || {} })); } catch {}
    useProfile(id); location.hash = '';
  };
}
function renderNewProfile() {
  $('#view').innerHTML = `
    <section class="welcome card">
      <div class="label">New profile</div>
      <h1>Start my plan</h1>
      <form id="npForm" class="npform">
        <label><span>Your name <span class="opt-note">(optional)</span></span><input id="npName" maxlength="30" autocomplete="given-name" placeholder="e.g. Arnav"></label>
        <label id="npPassL" hidden>Passcode <input id="npPass" type="password" autocomplete="current-password"></label>
        <label id="npStartL">Start date <input id="npStart" type="date" value="${todayISO()}" required></label>
        <div id="npMsg" class="np-msg" hidden></div>
        <p class="muted" style="font-size:14px;margin:0">From this day you get ${NEW_PER_DAY} new problems a day in NeetCode order, plus up to ${DAILY_CAP} revisions. Already solved some? Tap the circle next to a problem on the home page to tick it.</p>
        <div style="display:flex;gap:8px;flex-wrap:wrap"><button class="btn primary" type="submit">Start →</button><a class="btn" href="${S.profiles.active ? '#' : '#welcome'}">Cancel</a></div>
      </form>
    </section>`;
  $('#npName').focus();
  const isOwnerName = () => $('#npName').value.trim().toLowerCase() === OWNER_NAME.toLowerCase();
  $('#npName').oninput = () => { const o = isOwnerName(); $('#npPassL').hidden = !o; $('#npStartL').hidden = o; $('#npMsg').hidden = true; };
  $('#npForm').onsubmit = async e => {
    e.preventDefault();
    const name = $('#npName').value.trim() || 'User', start = $('#npStart').value || todayISO();
    // no name entered: start straight away as "User"
    if (isOwnerName()) {
      let okp = false; try { okp = (await sha256('dsa-journal:' + $('#npPass').value.trim())) === OWNER_HASH; } catch {}
      if (!okp) { const m = $('#npMsg'); m.hidden = false; m.textContent = `That name is taken. Enter its passcode, or pick another name.`; return; }
      markOwnerBrowser(); saveProfiles({ ...S.profiles, active: 'owner' }); useProfile('owner'); location.hash = ''; return;
    }
    const id = Date.now().toString(36);
    saveProfiles({ active: id, list: [...(S.profiles.list || []), { id, name, start }] });
    useProfile(id); location.hash = '';
  };
}

/* ---------- ticking: tap the circle next to a problem to mark it solved (profiles only) ---------- */
function dotHTML(p, on) {
  if (isOwner()) return `<span class="dot${on ? ' on' : ''}" title="${on ? 'Solved' : 'Not yet'}"></span>`;
  return `<span class="dot tick${on ? ' on' : ''}" role="checkbox" tabindex="0" aria-checked="${!!on}" data-tick="${p.slug}" title="${on ? 'Solved · tap to untick' : 'Tap when solved'}" aria-label="#${p.id} ${esc(p.title)} solved"></span>`;
}
function toggleTick(slug) {
  const p = S.bySlug[slug]; if (!p) return;
  if (p.solved) {
    const n = (recOf(p).log || []).length;
    if (n && !confirm(`Untick #${p.id}? Its ${n} logged attempt${n === 1 ? '' : 's'} will be removed too.`)) return;
    setSolved(p, false);
  } else setSolved(p, true);
  // redraw the home page in place: same scroll position, same patterns open
  const open = $$('details.cat').map(d => d.open), y = scrollY;
  renderHome();
  $$('details.cat').forEach((d, k) => { d.open = !!open[k]; });
  scrollTo(0, y);
  const again = $(`[data-tick="${CSS.escape(slug)}"]`); if (again) again.focus({ preventScroll: true });
}
document.addEventListener('click', e => {
  const t = e.target.closest('[data-tick]'); if (!t) return;
  e.preventDefault(); e.stopPropagation(); toggleTick(t.dataset.tick);
}, true);
document.addEventListener('keydown', e => {
  const t = e.target.closest && e.target.closest('[data-tick]');
  if (t && (e.key === ' ' || e.key === 'Enter')) { e.preventDefault(); toggleTick(t.dataset.tick); }
});

/* ---------- a profile's Today card and plan page ---------- */
function plRow(p, done, extra = '', tick = true) {
  return `<li class="${done ? 'done' : ''}"><a href="#${p.slug}">
    ${tick ? dotHTML(p, done) : '<span class="dot on"></span>'}<span class="num">#${p.id}</span><span class="t">${esc(p.title)}</span>
    <span class="meta">${extra}${p.folder ? '<span class="pill notes">notes</span>' : ''}<span class="diff ${p.difficulty}">${p.difficulty[0]}</span></span></a></li>`;
}
function todayParts() {
  const fresh = planToday(), dueAll = revisionsDue(), revs = dueAll.slice(0, DAILY_CAP);
  const revDoneToday = S.all.filter(p => p.solved && (recOf(p).log || []).some(l => l.d === todayISO()) && !fresh.includes(p));
  return { fresh, revs, more: dueAll.length - revs.length, revDoneToday };
}
function todayCard(full) {
  const u = S.user;
  if (!planStarted()) {
    const d = daysUntil(u.start), ahead = planAhead(1)[0];
    return `<section class="card daily"><div class="daily-head"><div><div class="label">Your plan</div><h2 style="margin-top:4px">Starts ${d === 1 ? 'tomorrow' : `in ${d} days`} · ${fmtDate(u.start)}</h2></div></div>
      ${ahead ? `<div class="muted" style="font-size:14px">Day 1 will be:</div><ul class="plist daily-list">${ahead.fresh.map(p => plRow(p, false)).join('')}</ul>` : ''}</section>`;
  }
  const { fresh, revs, more, revDoneToday } = todayParts();
  const nDone = fresh.filter(p => p.solved).length, left = planOrder().length;
  const finish = addDays(todayISO(), Math.ceil(Math.max(0, left - (fresh.length - nDone)) / NEW_PER_DAY));
  return `<section class="card daily">
    <div class="daily-head"><div><div class="label">${unnamed(u) ? 'Your' : esc(u.name) + "'s"} plan · day ${planDay()}</div><h2 style="margin-top:4px">Today · ${fmtDate(todayISO())}</h2></div>
      <span class="pill ${fresh.length && nDone === fresh.length ? 'ok' : 'soon'}">${nDone}/${fresh.length} new done</span></div>
    <div class="label" style="margin-top:4px">${fresh.length ? `${NEW_PER_DAY} new problems` : 'New problems'}</div>
    ${fresh.length ? `<ul class="plist daily-list">${fresh.map(p => plRow(p, p.solved)).join('')}</ul>
      <div class="muted" style="font-size:13px">Solve each on LeetCode, then tap its circle. Anything left over moves to tomorrow.</div>`
      : '<div class="muted" style="font-size:14px">You\'ve gone through all 150. Revisions keep coming below.</div>'}
    <div class="label" style="margin-top:8px">Revisions (max ${DAILY_CAP})</div>
    ${revs.length ? `<ul class="plist daily-list">${revs.map(p => { const d = dueIn(p); return plRow(p, false, `<span class="pill due">${d < 0 ? `${-d}d late` : 'due'}</span>`, false); }).join('')}</ul>
      <div style="display:flex;gap:8px;align-items:center;flex-wrap:wrap"><a class="btn primary sm" href="#revise">Start timed revision →</a>${more > 0 ? `<span class="muted" style="font-size:13px">${more} more due; they come up on the next days.</span>` : ''}</div>`
      : `<div class="muted" style="font-size:14px">${revDoneToday.length ? `Done for today: ${revDoneToday.length} revised.` : 'Nothing due today.'}</div>`}
    ${full ? '' : `<div class="muted" style="font-size:13px;border-top:1px solid var(--line);padding-top:10px">${left ? `At ${NEW_PER_DAY} a day you finish all 150 around <b>${fmtDate(finish)}</b>.` : 'All 150 done.'}</div>`}
  </section>`;
}
/* ---------- a profile's progress file (History) ---------- */
function progressJSON() { const ud = udata(); return JSON.stringify({ app: 'dsa-journal', v: 1, name: S.user.name, start: S.user.start, solved: ud.solved, rev: ud.rev, days: ud.days }, null, 1); }
function parseProgress(t) {
  try { const o = JSON.parse(t); if (!o || o.app !== 'dsa-journal' || typeof o.name !== 'string' || typeof o.solved !== 'object' || typeof o.rev !== 'object') return null;
    return { ...o, name: o.name.slice(0, 30), start: /^\d{4}-\d{2}-\d{2}$/.test(o.start || '') ? o.start : todayISO() }; } catch { return null; }
}
function progressBox() {
  return `<div class="card" style="display:flex;flex-direction:column;gap:10px">
    <div class="label">Export / import my progress</div>
    <div class="muted" style="font-size:14px">Your progress (solved problems, plan and revisions) is saved in this browser only. To use it on another device, press Export, send the text to yourself, and on the other device choose Start → "Import your progress" (or paste it here and press Import, which replaces this profile's progress).</div>
    <textarea class="io" id="io" spellcheck="false">${esc(progressJSON())}</textarea>
    <div style="display:flex;gap:8px;flex-wrap:wrap"><button class="btn primary" id="cp">Export (copy)</button><button class="btn" id="im">Import pasted progress</button><span id="iomsg" class="muted" style="font-size:13px;align-self:center"></span></div>
  </div>`;
}
function bindProgressBox() {
  $('#cp').onclick = async () => {
    try { await navigator.clipboard.writeText($('#io').value); $('#iomsg').textContent = 'Copied.'; }
    catch { $('#io').select(); $('#iomsg').textContent = 'Selected. Press Ctrl/Cmd + C.'; }
  };
  $('#im').onclick = () => {
    const o = parseProgress($('#io').value);
    if (!o) { $('#iomsg').textContent = "That isn't an exported progress file. Export it again on the other device."; return; }
    if (!confirm(`Replace ${S.user.name}'s progress here with the pasted one (${Object.keys(o.solved).length} solved)?`)) return;
    S.ud = { solved: o.solved, rev: o.rev, days: o.days || {} }; saveUD();
    saveProfiles({ ...S.profiles, list: S.profiles.list.map(u => u.id === S.user.id ? { ...u, name: o.name, start: o.start } : u) });
    useProfile(S.user.id); renderHistory(); $('#iomsg').textContent = 'Imported.';
  };
}

/* ---------- info dialog ---------- */
const dlg = $('#info');
$('#infoBtn').onclick = () => { if (dlg.showModal) dlg.showModal(); else dlg.setAttribute('open', ''); };
$('#infoClose').onclick = () => dlg.close ? dlg.close() : dlg.removeAttribute('open');
dlg.addEventListener('click', e => { if (e.target === dlg) dlg.close(); });
$$('[data-itab]').forEach(b => b.onclick = () => {
  $$('[data-itab]').forEach(x => x.setAttribute('aria-pressed', x === b));
  $$('[data-ipane]').forEach(x => x.hidden = x.dataset.ipane !== b.dataset.itab);
});

boot();
