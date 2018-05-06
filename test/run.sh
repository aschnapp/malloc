#!/bin/bash
export DYLD_LIBRARY_PATH="/Users/alexanderschnapp/Documents/Education/42/malloc/"
export DYLD_INSERT_LIBRARIES="libft_malloc_x86_64_Darwin.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
