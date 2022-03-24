#!/bin/bash
set -e

EMCC=emcc
JOBS=1
MYDIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

stage1() {
sh $MYDIR/sys/unix/setup.sh
make CC=$EMCC -j$JOBS

make install CC=$EMCC PREFIX=$MYDIR/build
#rm $MYDIR/build/nethack/nethack
#rm $MYDIR/build/nethack/recover
cp $MYDIR/web/nethackrc.default $MYDIR/build/nethack/
cp $MYDIR/src/browserhack.js web/
cp $MYDIR/src/browserhack.wasm web/
cp $MYDIR/src/browserhack.data web/
}

# stage2() {
# pushd build
#   cp ../src/nethack.wasm nethack.bc
#   $EMCC nethack.bc \
#     -O3 \
#     -Oz \
#     -o browserhack.js \
#     -s EMTERPRETIFY=1 \
#     -s EMTERPRETIFY_ASYNC=1 \
#     --memory-init-file 1 \
#     --js-library ../win/web/nethack_lib.js \
#     --preload-file nethack \

# popd
# cp build/browserhack.js web/
# cp build/browserhack.wasm web/
# cp build/browserhack.data web/

# pushd web
#   python ../win/web/tile2name.py
# popd
# }

stage1
#stage2
