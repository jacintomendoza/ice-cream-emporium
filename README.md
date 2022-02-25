# Mav's Ice Cream Emporium
Ice-cream C++ GUI application written in the Spring of 2018.

Previously written on a Linux machine, it has been updated to work with a Mac with C++'s GTK interface, gtkmm.  May need to change the Makefile and the included libraries on line 17 to run on your machine.


## Needed/preferred for MacOS users:
- Xcode
- gtkmm
- brew install pkg-config     
- adwaita icon theme

### Some useful terminal commands:
```
brew install gtkmm
brew install adwaita-icon-theme
```

## Compiling
### Please run the following code via the root to run the program and replace existing object files
```
make
```

### To remove object files
```
make clean
```

### Other compiling commands included in Makefile
```
make test
make debug
make all
```

## Other info
### File -> Easteregg: automatically adds preconfigured containers, scoops, toppings, servers and customers
![Screen Shot 2022-02-24 at 9 13 44 PM (2)](https://user-images.githubusercontent.com/55859236/155647027-b2b2ee93-5208-4e86-b1ce-45edae86cbd9.png)

### Please refer to User_Interface.pdf for more info on the app
