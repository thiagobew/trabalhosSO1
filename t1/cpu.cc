#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save() {
  // adicionar implementação
}

void CPU::Context::load() {
  // adicionar implementação
}

CPU::Context::~Context() {
  // adicionar implementação
}

void CPU::switch_context(Context *from, Context *to) {
  from->save();
  to->load();
}

__END_API
