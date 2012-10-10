#!/bin/sh

owd="$PWD"
containing_dir="$( cd "$( dirname "$0" )" && pwd )"

# prepare libetpan
echo "bootstrapping libetpan" 1>&2
libetpan_dir="$containing_dir/../lib/libetpan/build-mac"
cd "$libetpan_dir"
./update.sh
if [ $? -ne 0 ]; then
  echo "bootstrapping libetpan failed" 1>&2
  cd "$owd"
  exit 1
fi

cd "$owd"
