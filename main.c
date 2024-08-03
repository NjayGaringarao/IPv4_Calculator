#include <stdio.h>
#include <stdint.h>

//input variables
char userInput[20];
int octet1, octet2, octet3, octet4, cIDR;

//32bit Version Variables
uint32_t iPAddress;
uint32_t mValue;
uint32_t networkID;
uint32_t broadcastID;

//8bit Version Variables
uint8_t mask[4], nID[4], bID[4];
uint8_t firstIP[4], lastIP[4];

void input() {

    int inputChecker;

    do{
        printf("\n----------------------------------------------------------------");
        printf("\nEnter the IP Address: ");
        scanf("%s", userInput);

        //validation
        int wrong;
        int octet = sscanf(userInput, "%d.%d.%d.%d/%d%d", &octet1, &octet2, &octet3, &octet4, &cIDR, &wrong);
        if (octet != 5 || octet1 < 0 || octet1 > 223 || octet2 < 0 || octet2 > 255 ||
            octet3 < 0 || octet3 > 255 || octet4 < 0 || octet4 > 255 || cIDR > 31 || cIDR < 0) {
            printf("\n----------------------------------------------------------------");
            printf("\nInvalid IP address! Please try again.");
        } else {
            inputChecker = 1;
        }
    } while (inputChecker != 1);
}

void mainProcess() {

    //Conversion and formula
    iPAddress = (octet1 << 24)|(octet2 << 16)|(octet3 << 8)| octet4;
    mValue = 0b11111111111111111111111111111111u << (32 - cIDR);

    networkID = iPAddress & mValue;
    broadcastID = networkID | ~mValue;

    //Pag bounce in sa 8bit
    for(int i = 0; i < 4; i++) {
        mask[i] = (mValue >> (24 - (8 * i))) & 0b11111111;
        nID[i] = (networkID >> (24 - (8 * i))) & 0b11111111;
        bID[i] = (broadcastID >> (24 - (8 * i))) & 0b11111111;
        firstIP[i] = nID[i];
        lastIP[i] = bID[i];
    }

    firstIP[3]++;
    lastIP[3]--;

}





void printer(){
    printf("\n----------------------------------------------------------------");
    printf("\nNetwork ID               : %d.%d.%d.%d", nID[0], nID[1], nID[2], nID[3]);
    printf("\nFirst/Last Usable IP     : %d.%d.%d.%d / %d.%d.%d.%d", firstIP[0], firstIP[1], firstIP[2], firstIP[3], lastIP[0], lastIP[1], lastIP[2], lastIP[3]);
    printf("\nBroadcast ID             : %d.%d.%d.%d", bID[0], bID[1], bID[2], bID[3]);
    printf("\nSubnet Mask              : %d.%d.%d.%d", mask[0], mask[1], mask[2], mask[3]);
    printf("\n----------------------------------------------------------------");
}

int main(){
    int mainLoop;
    char userChoice;

    printf("Welcome to IPv4 calculator");
    printf("\n----------------------------------------------------------------");

    do{

        input();
        mainProcess();
        printer();

        printf("\nDo you want to calculate IP address again? ");
        int x = 0;

        do {
            printf("\nInstruction: Enter y if you want to continue. If not, enter n: ");
            scanf(" %c", &userChoice);
            scanf("%*[^\n]");

            if (userChoice == 'y') {
                mainLoop = 1;
                x = 1;
            } else if (userChoice == 'n') {
                mainLoop = 0;
                x = 1;
            } else {
                printf("Invalid input. Please enter y or n.\n");

            }
        } while (x == 0);

    }while(mainLoop == 1);

    printf("\n----------------------------------------------------------------");
    printf("\nProgram by Niño Jr Garingarao");
    printf("\n----------------------------------------------------------------");
    printf("\nEnter any character to exit ");
    scanf(" %d", &octet1);

}
