# Rachel SDK simulator
SDk simulator of project Rachel
## Usage

### Get submodules

```
./fetch_submodules.sh
```

### Install SDL
You can download SDL from https://www.libsdl.org/

On on Linux you can install it via terminal:
```
sudo apt-get update && sudo apt-get install -y build-essential libsdl2-dev
```

### Build and run 

```
mkdir build && cd build
```

```
cmake .. && make
```

```
./LGFX_SDL
```

