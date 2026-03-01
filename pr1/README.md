# Pr1 (Variant 1)
Purpose: To learn the process of installing and starting up Ubuntu Linux, setting up basic environment for programing in C/C++ languages.

## Installation Ubuntu Server
1. First of all need to install VirtualBox for Ubuntu Server -  https://www.virtualbox.org/wiki/Downloads
2. Download Ubuntu Server iso image - https://ubuntu.com/download/server
3. After installation VirtualBox open it and click New button.
![](readme_imgs/1.png)
4. On the pop up window name your virtual machine and provide path to your ISO Image.
![](readme_imgs/2.png)
5. Then proced to "Set up unattended guest OS installation". Here you need to enter your future user name and password for you system.
![](readme_imgs/3.png)
6. In "Specify virtual hardware" you can configurate how much resources you can allocate for you virtual machine (I recommend to bump up to 2 cpu cores).
![](readme_imgs/4.png)
7. In final menu "Specify virtual hard disk" you can select size of memory for your server. 25 gb is enough for me so I click finish button.
![](readme_imgs/5.png)
8. Now you have virtual machine, click on it and press start.
![](readme_imgs/6.png)
9. In this language options pick English.
![](readme_imgs/7.png)
10. In future steps I did'nt change anything so I selected "Done" and hit enter.
![](readme_imgs/8.png)
![](readme_imgs/9.png)
![](readme_imgs/10.png)
![](readme_imgs/11.png)
![](readme_imgs/12.png)
![](readme_imgs/13.png)
![](readme_imgs/14.png)
11. Type in your name, pick a name for your server, username and password.
![](readme_imgs/15.png)
12. In last few steps I skiped all settings. After this steps installation begins.
![](readme_imgs/16.png)
![](readme_imgs/17.png)
13. After you reboot you virtual machine you have installed your Ubuntu server.

## Setting up Ubuntu Server
To write first program you need to intall essetial utilities by writing commands below:
- sudo ubuntu-drivers autoinstall
- sudo reboot
- sudo apt install build-essential git -y

Last commands install gcc, g++ cimpilers and git so now your system completely configured.

## Implementing the first program in C
### Task 1.1
---

У наступній програмі використовується математична бібліотека. Вам потрібно:

1. Правильно скомпілювати програму з використанням бібліотеки math.h.

2. Додати обробку помилок, щоб перевірити правильність виклику erf.

3. Розширити програму, щоб вона обчислювала довірчі інтервали не тільки для 95%, але й для 90% і 99%.

4. Додати можливість введення значень від користувача для довірчого інтервалу.


```
#include <math.h>
#include <stdio.h>

int main  {
    double z;
    printf("Enter Z-score: ");
    if (scanf("%lf", &z) != 1) {
        fprintf(stderr, "Invalid input!\n");
        return 1;
    }
    printf("The integral of a Normal (0,1) distribution "
           "between -Z and Z i’s: %g\n", erf(z * sqrt(1/2.)));(знайти помилку)

    return 0;
}
```

5. Додайте підтримку обчислення довірчого інтервалу для розподілу Стьюдента.

6. Реалізуйте програму як окремий модуль (erf_module.c + erf_module.h) і використовуйте її у головному файлі main.c.

7. Скомпілюйте програму з оптимізацією O2 або O3 і перевірте різницю у продуктивності.

### Solivng results
---
7. Скомпілюйте програму з оптимізацією O2 або O3 і перевірте різницю у продуктивності.

To check optimization difference I create file 'input.txt' containing sequences of option inputs in the program for testing the function 'find_z_by_confidence_level()', because it puts the most load on the processor among other functions.

Also in Makefile I create compile commands 'make mainO2' and 'make mainO3' to compile with different optimization.

To test optimization difference I used commands below.
```
time ./mainO2 < input.txt
time ./mainO3 < input.txt
```
O2 perfomance:
![](readme_imgs/18.png)
O3 perfomance:
![](readme_imgs/19.png)

'user' shows pure time that the processor was running. As we can see, compiling the program with O3 optimization makes program run faster.
### Setup & Usage Instruction
---
Clone my solving using commands below.
```
git init

git remote add origin https://github.com/bebikmikhailo/SystemSoftwareArchitecturePrs.git

git config core.sparseCheckout true

echo "pr1/*" >> .git/info/sparse-checkout

git pull origin main
```
Commands to run program.
```
cd pr1

# Use 'make mainO2' or 'make mainO3' to compile program with O2 or O3 optimization levels.

make main 

./main
```

