// Lists every problems/<id>-<slug>/ folder that has a meta.json into problems/index.json.
// GitHub Actions runs this on every push, so you never edit index.json by hand.
import { readdirSync, existsSync, writeFileSync } from 'node:fs';
const dirs = readdirSync('problems', { withFileTypes: true })
  .filter(d => d.isDirectory() && !d.name.startsWith('_') && existsSync(`problems/${d.name}/meta.json`))
  .map(d => d.name)
  .sort((a, b) => parseInt(a) - parseInt(b));
writeFileSync('problems/index.json', JSON.stringify(dirs, null, 1) + '\n');
console.log(`problems/index.json: ${dirs.length} problem folders`);
