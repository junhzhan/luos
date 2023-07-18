BUILD:=./build

HD_IMG_NAME:= "hd.img"

all: boot.o setup.o
	rm -rf $(HD_IMG_NAME)
	bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat $(HD_IMG_NAME)
	dd if=boot.o of=hd.img bs=512 seek=0 count=1 conv=notrunc
	dd if=setup.o of=hd.img bs=512 seek=1 count=2 conv=notrunc

./%.o: ./%.asm
	nasm $< -o $@

clean:
	rm -rf *.o

bochs: all
	bochs -q -f bochsrc

qemu: all
	qemu-system-x86_64 -hda hd.img
