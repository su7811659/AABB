#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int
GenerateRandomAns(char *pszAns, int nAnsLen)
{
	int IsAdded[10];
	int i = 0;
	char szAns[nAnsLen + 1];

	memset(IsAdded, 0, sizeof(IsAdded));
	memset(szAns, 0, sizeof(szAns));

	szAns[nAnsLen + 1] = '\0';

	for (i = 0; i < nAnsLen; i++) {
		int num = 0;
		srand(time(NULL));
		do {
			num = rand() % 10;
		} while (IsAdded[num] == 1);

		snprintf(szAns + i, sizeof(szAns) - i, "%d", num);
		IsAdded[num] = 1;
	}

	strncpy(pszAns, szAns, nAnsLen);
	pszAns[nAnsLen + 1] = '\0';

	return 0;
}

int UserInputValidCheck(char *pszUserAns, int nAnsLen)
{
	int nErr = 0;
	int IsAdded[10];
	int i = 0;

	memset(IsAdded, 0, sizeof(IsAdded));

	if (strlen(pszUserAns) != nAnsLen) {
		printf("[ERROR] The length of answer you enter is wrong! Please enter %d characters!\n\n", nAnsLen);
		nErr = -1;
		goto end;
	}

	for (i = 0; i < nAnsLen; i++) {
		int CurNum = pszUserAns[i] - '0';

		if (pszUserAns[i] < '0' || pszUserAns[i] > '9') {
			printf("[ERROR] The answer you enter is %s! Please enter your answer with only 0 - 9!\n\n", pszUserAns);
			nErr = -2;
			goto end;
		}

		if (IsAdded[CurNum] == 1) {
			printf("[ERROR] The answer you enter is %s! Please enter your answer with no duplicate characters!\n\n", pszUserAns);
			nErr = -2;
			goto end;
		} else {
			IsAdded[CurNum] = 1;
		}
	}


end:

	return nErr;
}

int
UserAnswerCheck(char *pszAns, int nAnsLen, char *pszUserAns)
{
	int i = 0, j = 0;
	int A = 0;
	int B = 0;

	for (i = 0; i < nAnsLen; i++) {
		if (pszUserAns[i] == pszAns[i]) {
			A++;
		} else {
			for (j = 0; j < nAnsLen; j++) {
				if (pszUserAns[i] == pszAns[j]) {
					B++;
				}
			}
		}
	}

	if (A == nAnsLen) {
		printf("Result: [%dA] \nCongradulations! :))\n\n", A);
		return 1;
	} else {
		printf("Result: [%dA%dB] \nKeep going!\n\n", A, B);
		return 0;
	}

	return 0;
}


int
GuessAns(char *pszAns, int nAnsLen)
{
	char szUserAns[nAnsLen + 1];
	int IsPass = 0;

	memset(szUserAns, 0, sizeof(szUserAns));

	do {
		printf("Hi :D Please enter your answer(Enter \"BYE\" to give up and see answer): \n");
		scanf("%s", szUserAns);

		if (strncmp(szUserAns, "BYE", strlen(szUserAns)) == 0) {
			printf("Oh!So sad:(\nThe REAL Answer is %s\n\n", pszAns);
			break;
		}

		if (UserInputValidCheck(szUserAns, nAnsLen) == 0) {
			IsPass = UserAnswerCheck(pszAns, nAnsLen, szUserAns);
		}



	} while(IsPass != 1);

	return 0;
}

int main() {
	char Ans[10] = {0};
	int AnsDigt = 0;
	int IsDigtValid = 0;

	do {
		printf("please enter the number of digit you want to guess(range: 1 - 10):\n");
		scanf("%d", &AnsDigt);

		if (AnsDigt < 10 && AnsDigt > 0) {
			IsDigtValid = 1;
		} else {
			printf("[ERROR] The digit you enter is not valid! Please enter the number between 1 and 10!\n\n");
			AnsDigt = 0;
		}
	} while(IsDigtValid != 1);


	GenerateRandomAns(Ans, AnsDigt);
	Ans[AnsDigt] = '\0';

	GuessAns(Ans, AnsDigt);

	return 0;
}
