// Based on: https://nodejs.org/api/wasi.html
// $ node --experimental-wasi-unstable-preview1 ./test.js

import fs from 'fs';
import { WASI } from 'wasi';

const wasi = new WASI({
  args: process.argv,
  env: process.env,
  preopens: {
    '/sandbox': './sandbox',
  },
});
const importObject = { wasi_snapshot_preview1: wasi.wasiImport };

const wasm = await WebAssembly.compile(fs.readFileSync('./demo.wasm'));
const instance = await WebAssembly.instantiate(wasm, importObject);

wasi.start(instance);
