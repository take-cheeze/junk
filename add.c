// clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all add.c -o add.wasm -O3 -flto -Wl,--lto-O3 -Wl,-z,stack-size=$[8 * 1024 * 1024]

int add(int a, int b) {
  return a*a + b;
}

extern unsigned char __heap_base;

unsigned int bump_pointer = &__heap_base;
void* malloc(int n) {
  unsigned int r = bump_pointer;
  bump_pointer += n;
  return (void *)r;
}

void free(void* p) {
  // lol
}
