CC ?= armv8m-tcc
CFLAGS = -mno-pic-data-is-text-relative -fPIE -fpie -g -mcpu=cortex-m33 -fvisibility=hidden -I../../rootfs/usr/include -L../../rootfs/lib
LDFLAGS = -fpie -fPIE -fvisibility=hidden -g -Wl,-Ttext=0x0 -Wl,-section-alignment=0x4 -lncurses
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, build/%.o, $(SRCS))

TARGET = build/tv

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
INCLUDEDIR ?= $(PREFIX)/include

# Rules
all: $(TARGET) $(TARGET).elf

build/%.o: %.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@


$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -Wl,-oformat=elf32-littlearm $^ -o $@

install: $(TARGET) $(TARGET).elf
	mkdir -p $(BINDIR)
	cp $(TARGET) $(BINDIR)

clean:
	rm -rf build