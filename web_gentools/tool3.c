#include <stdlib.h>

void setup_centos() {
    system("sudo yum install httpd php mysql php-mysql");
    // TODO: Add more commands as needed
}

void setup_debian() {
    system("sudo apt-get install apache2 php mysql-server php-mysql");
    // TODO: Add more commands as needed
}

void setup_manjaro() {
    system("sudo pacman -S apache php mysql php-mysql");
    // TODO: Add more commands as needed
}

int main() {
    int choice;
    // TODO: Add code to get choice from user input
    switch (choice) {
        case 1:
            setup_centos();
            break;
        case 2:
            setup_debian();
            break;
        case 3:
            setup_manjaro();
            break;
    }
    return 0;
}