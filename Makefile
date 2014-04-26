all: 
	echo "Building"
	cd src && make

clean: 
	echo "Cleaning"
	cd src && make clean

watch:
	watch -n 1 --color make

run:
	qemu-system-i386 --kernel src/kernel
