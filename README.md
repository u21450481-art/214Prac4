# TaskForge — COS 214 Practical 4

All commands below run inside Docker. Docker is the only requirement on the host machine.

## Build

From the repository root:

```bash
docker build -t taskforge .
```

The program is compiled during the image build.

## Run the program

```bash
docker run --rm taskforge
```

## Run under GDB

Docker blocks the `ptrace` system call by default, which GDB requires. The two flags below enable it.

```bash
docker run --rm -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined taskforge gdb ./taskforge
```

## Run under Valgrind

```bash
docker run --rm --cap-add=SYS_PTRACE --security-opt seccomp=unconfined taskforge valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

