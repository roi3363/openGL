SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
BUILD_DIR="$SCRIPT_DIR/build"
mkdir -p "$BUILD_DIR"
cmake "$SCRIPT_DIR" -B "$BUILD_DIR" || exit
make -C "$BUILD_DIR" || exit
"$BUILD_DIR/graphics"
