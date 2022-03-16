# Abort the script at the first error
set -e

make

if [ "$1" == "" ]; then
	SCENE="./scene/camera.rt"
else
	SCENE="./scene/$1"
fi

./minirt $SCENE
