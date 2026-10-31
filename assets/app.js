/* DSA Journal — static single-page app. Data lives in data/ and problems/. */
const INTERVALS = [1, 3, 7, 14, 30, 60];          // days until next review, by box
const DAILY_CAP = 4;                              // most problems scheduled on any one day
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

const S = { cats: [], all: [], bySlug: {}, folders: {}, patterns: {}, repoRev: {}, cache: {},
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

/* ---------- revision store (repo file as base, browser on top) ---------- */
function localRev() { try { return JSON.parse(localStorage.getItem(STORE_KEY) || '{}') || {}; } catch { return {}; } }
function saveLocal(obj) { try { localStorage.setItem(STORE_KEY, JSON.stringify(obj)); } catch {} }
function allRev() {
  const out = { ...(S.seeded || {}), ...S.repoRev }, loc = localRev();
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
      if (cnt >= DAILY_CAP && target > 3) continue;   // short gaps (1–3 days) stay on time even on a busy day
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
  S.seeded = loc;
}

function rate(p, result, secs) {
  const r = JSON.parse(JSON.stringify(recOf(p)));
  if (result === 'fast') r.box = Math.min((r.box || 0) + 1, INTERVALS.length - 1);
  else if (result === 'fail') r.box = 0;
  else r.box = r.box || 0;
  r.due = nextDue(p, result === 'fail' ? 1 : INTERVALS[r.box], dayLoad(p.slug));
  r.log = [...(r.log || []), { d: todayISO(), s: Math.round(secs), r: result }];
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
    const [cats, pats, folders, repoRev] = await Promise.all([
      getJSON('data/catalog.json'), getJSON('data/patterns.json'),
      getJSON('problems/index.json').catch(() => []), getJSON('data/revisions.json').catch(() => ({}))
    ]);
    S.cats = cats; S.patterns = pats; S.repoRev = repoRev || {};
    folders.forEach(f => { const id = parseInt(f, 10); if (id) S.folders[id] = f; });
    cats.forEach(c => c.problems.forEach(p => {
      p.slug = slugify(p.title); p.cat = c; p.folder = S.folders[p.id] || null;
      S.all.push(p); S.bySlug[p.slug] = p;
    }));
  } catch (e) {
    $('#view').innerHTML = `<div class="empty"><b>Couldn't load the data files.</b><br>Open this site through a web server (GitHub Pages, or run <code>npx serve .</code> in the repo folder), not by double-clicking index.html.</div>`;
    return;
  }
  seedSchedule();
  window.addEventListener('hashchange', route);
  route();
}

function route() {
  const h = decodeURIComponent(location.hash.slice(1));
  $$('.top nav a').forEach(a => a.classList.toggle('on', a.dataset.nav === (h === 'revise' || h === 'history' ? h : (h ? '' : 'home'))));
  if (h === 'revise') renderRevise();
  else if (h === 'history') renderHistory();
  else if (S.bySlug[h]) renderProblem(S.bySlug[h]);
  else renderHome();
  window.scrollTo(0, 0);
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
  const dueAll = S.all.filter(p => p.solved && dueIn(p) <= 0);
  const pct = n => (100 * n / cs.length).toFixed(2);
  $('#view').innerHTML = `
    <section class="hero">
      <div class="card">
        <div class="label">NeetCode 150</div>
        <div class="big" style="margin:8px 0 12px">${solved.length}<small> / ${cs.length} solved</small></div>
        <div class="bar"><i style="width:${pct(by('Easy'))}%;background:var(--easy)"></i><i style="width:${pct(by('Medium'))}%;background:var(--med)"></i><i style="width:${pct(by('Hard'))}%;background:var(--hard)"></i></div>
        <div class="split"><span><b>${by('Easy')}</b>/${tot('Easy')} Easy</span><span><b>${by('Medium')}</b>/${tot('Medium')} Medium</span><span><b>${by('Hard')}</b>/${tot('Hard')} Hard</span><span><b>${Object.keys(S.folders).length}</b> with full notes</span></div>
      </div>
      <div class="card due-card">
        <div><div class="label">Due for revision</div>
        <div class="big" style="margin-top:8px">${dueAll.length}<small> problem${dueAll.length === 1 ? '' : 's'}</small></div></div>
        <div class="muted" style="font-size:14px">Pick a pattern and re-solve one under a timer, running the 8 steps.</div>
        <div><a class="btn primary" href="#revise">Start timed revision →</a></div>
      </div>
    </section>
    <section style="display:flex;flex-direction:column;gap:12px">
      <div style="display:flex;align-items:baseline;gap:12px;flex-wrap:wrap"><h2>Patterns</h2><span class="muted" style="font-size:14px">Tap a pattern to see its problems. Red border = you failed one there recently.</span></div>
      <div class="cats">${S.cats.map(catCard).join('')}</div>
    </section>`;
}

function catCard(c) {
  const st = catStats(c), pat = S.patterns[c.slug] || {};
  const open = st.solved > 0 && !c.extra ? '' : '';
  const badge = st.weak ? `<span class="pill weak">${st.weak} weak</span>` : st.due ? `<span class="pill due">${st.due} due</span>` : st.solved ? `<span class="pill ok">up to date</span>` : '';
  return `<details class="cat${st.weak ? ' weak' : ''}"${open}>
    <summary>
      <div class="cat-head"><span class="chev">▸</span><h3>${esc(c.name)}</h3>${badge}<span class="cat-count">${st.solved}/${st.total}</span></div>
      <div class="bar" style="height:6px"><i style="width:${100 * st.solved / st.total}%;background:var(--accent)"></i></div>
      ${pat.spot ? `<div class="spot"><b>Spot it:</b> ${esc(pat.spot)}</div>` : ''}
    </summary>
    <ul class="plist">${c.problems.map(p => `<li class="${p.solved ? '' : 'todo'}"><a href="#${p.slug}">
      <span class="dot${p.solved ? ' on' : ''}" title="${p.solved ? 'Solved' : 'Not yet'}"></span>
      <span class="num">#${p.id}</span>
      <span class="t">${esc(p.title)}</span>
      <span class="meta">${p.folder ? '<span class="pill notes">notes</span>' : ''}${duePill(p)}<span class="diff ${p.difficulty}">${p.difficulty[0]}</span></span>
    </a></li>`).join('')}</ul>
  </details>`;
}

/* ---------- problem page ---------- */
async function renderProblem(p) {
  const v = $('#view');
  const lc = `https://leetcode.com/problems/${p.slug}/`;
  const rec = recOf(p);
  const head = `
    <a class="crumb" href="#"><span class="arr" aria-hidden="true">←</span>${esc(p.cat.name)}</a>
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
      <button class="btn primary" id="reviseThis">Re-solve with timer</button>
    </div>` : '';
  const nav = pnav(p);

  if (!p.folder) {
    v.innerHTML = `${head}${revCard}
      <div class="empty"><b>Notes not written yet.</b><br>Copy <code>problems/_template</code> to <code>problems/${p.id}-${p.slug}</code>, fill in the 8 steps and your code, then push.</div>${nav}`;
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
        <div class="vizcta-btns"><button class="btn primary" data-viz="${i}">▶ Show visualizer</button><a class="btn sm" href="${esc(a.viz)}" target="_blank" rel="noopener">Full page ↗</a></div>
      </div><div data-vizbox="${i}"></div>` : ''}
      <div class="codebox"><button class="btn sm copy" data-copy="${i}">Copy</button><pre><code class="language-cpp">${esc(codes[i] || '// file missing: ' + a.file)}</code></pre></div>
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
  $$('[data-viz]', v).forEach(b => b.onclick = () => {
    const box = $(`[data-vizbox="${b.dataset.viz}"]`, v);
    if (box.firstChild) { box.innerHTML = ''; b.textContent = '▶ Show visualizer'; return; }
    box.innerHTML = `<iframe class="vizframe" src="${esc(meta.approaches[+b.dataset.viz].viz)}" title="Visualizer"></iframe>`;
    b.textContent = 'Hide visualizer';
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
function bindReviseThis(p) {
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
      </div>
      <div class="card"><div class="label" style="margin-bottom:8px">Run the 8 steps out loud</div>
        <ul class="checklist">${STEPS.map((s, i) => `<li><label><input type="checkbox" id="st${i}"><span>${i + 1}. ${esc(s)}</span></label></li>`).join('')}</ul>
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

  $$('[data-pat]').forEach(b => b.onclick = () => { S.rev.pattern = b.dataset.pat; resetSession(); renderRevise(); });
  const tb = $('#tbtn'); if (tb) tb.onclick = () => S.rev.running ? pauseTimer() : startTimer();
  const sk = $('#skip'); if (sk) sk.onclick = () => {
    const list = pool(S.rev.pattern).sort((a, b) => dueIn(a) - dueIn(b));
    const nxt = list[(list.indexOf(S.rev.cur) + 1) % list.length]; resetSession(); S.rev.cur = nxt; renderRevise();
  };
  $$('[data-rate]').forEach(b => b.onclick = () => { const secs = elapsed(); stopTimer(); rate(S.rev.cur, b.dataset.rate, secs); S.rev.rated = b.dataset.rate; renderRevise(); });
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
    <div class="card" style="display:flex;flex-direction:column;gap:10px">
      <div class="label">Sync between devices</div>
      <div class="muted" style="font-size:14px">Your revisions save in this browser. To keep them on GitHub (and on your phone), copy this, paste it into <code>data/revisions.json</code> in the repo, and push. To load revisions here, paste JSON and press Import.</div>
      <textarea class="io" id="io" spellcheck="false">${esc(JSON.stringify(rev, null, 1))}</textarea>
      <div style="display:flex;gap:8px;flex-wrap:wrap"><button class="btn primary" id="cp">Copy</button><button class="btn" id="im">Import pasted JSON</button><span id="iomsg" class="muted" style="font-size:13px;align-self:center"></span></div>
    </div>`;
  $('#cp').onclick = async () => {
    try { await navigator.clipboard.writeText($('#io').value); $('#iomsg').textContent = 'Copied.'; }
    catch { $('#io').select(); $('#iomsg').textContent = 'Selected. Press Ctrl/Cmd + C.'; }
  };
  $('#im').onclick = () => {
    try { const o = JSON.parse($('#io').value); if (typeof o !== 'object' || Array.isArray(o)) throw 0; saveLocal(o); $('#iomsg').textContent = 'Imported.'; renderHistory(); }
    catch { $('#iomsg').textContent = "That isn't valid revisions JSON. Copy it again from the other device."; }
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
