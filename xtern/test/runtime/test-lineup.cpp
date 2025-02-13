/* Copyright (c) 2013,  Regents of the Columbia University 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other 
 * materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// RUN: %srcroot/test/runtime/run-scheduler-test.py %s -gxx "%gxx" -llvmgcc "%llvmgcc" -projbindir "%projbindir" -ternruntime "%ternruntime" -ternannotlib "%ternannotlib"  -ternbcruntime "%ternbcruntime"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <semaphore.h>
#include "tern/user.h"

pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;

void loop(const char *tag) {
  const int loopCount = 50;
  for (int i = 0; i < loopCount; i++) {
    soba_wait(0);
    pthread_mutex_lock(&mu);
    printf("%s\n", tag);
    pthread_mutex_unlock(&mu);
  }
}

void* thread_func(void*) {
  loop("SECOND");
}

int main(int argc, char *argv[], char* env[]) {
  int ret;
  pthread_t th;
  soba_init(0, 2, 20);
  ret  = pthread_create(&th, NULL, thread_func, NULL);
  assert(!ret && "pthread_create() failed!");
  loop("FIRST");
  pthread_join(th, NULL);
  return 0;
}

// CHECK: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND
// CHECK-NEXT: SECOND
// CHECK-NEXT: FIRST
// CHECK-NEXT: FIRST
// CHECK-NEXT: SECOND

