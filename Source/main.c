#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct grade {
	char name[10];
	int value;
	int weight;
	char date[20];
	char classroom[20];
};

struct note {
	char note[256];
};

struct course {
	char name[32];
	int missed;
	int weeklyHours;
	int limit;
	struct note notes[24];
	int noteCount;
	struct grade grades[12];
	int gradeCount;
	int credit;
	int gradeCur;
	int gradeMax;
	char gradeLetter[3];
	char gradeLetterMax[3];
};


int FirstTimeSetupCheck()
{
	FILE *dataStream;
	dataStream = fopen("data.txt", "r");
	if (dataStream == NULL) {
		return 1;
	}else {
		fclose(dataStream);
		return 0;
	}

}


void UpdateIntegerGrading(struct course *courseTable, int self)
{
	int i, score = 0, maxPossible = 100;
	for (i = 0; i < courseTable[self].gradeCount; i++) {
		score += courseTable[self].grades[i].value * courseTable[self].grades[i].weight / 100;
		maxPossible -= courseTable[self].grades[i].weight;
	}
	courseTable[self].gradeMax = score + maxPossible;
	courseTable[self].gradeCur = score;
}


void UpdateLetterGrading(struct course *courseTable, int self)
{
	if (courseTable[self].credit != 0) {
		if (courseTable[self].missed >= courseTable[self].limit) {
			strcpy(courseTable[self].gradeLetter, "NA");
			strcpy(courseTable[self].gradeLetterMax, "NA");
			courseTable[self].gradeCur = 0;
			courseTable[self].gradeMax = 0;
		}
		else if (courseTable[self].gradeCur >= 90) {
			strcpy(courseTable[self].gradeLetter, "AA");
		}
		else if (courseTable[self].gradeCur >= 85) {
			strcpy(courseTable[self].gradeLetter, "BA");
		}
		else if (courseTable[self].gradeCur >= 80) {
			strcpy(courseTable[self].gradeLetter, "BB");
		}
		else if (courseTable[self].gradeCur >= 75) {
			strcpy(courseTable[self].gradeLetter, "CB");
		}
		else if (courseTable[self].gradeCur >= 70) {
			strcpy(courseTable[self].gradeLetter, "CC");
		}
		else if (courseTable[self].gradeCur >= 65) {
			strcpy(courseTable[self].gradeLetter, "DC");
		}
		else if (courseTable[self].gradeCur >= 60) {
			strcpy(courseTable[self].gradeLetter, "DD");
		}
		else if (courseTable[self].gradeCur >= 50) {
			strcpy(courseTable[self].gradeLetter, "FD");
		}
		else {
			strcpy(courseTable[self].gradeLetter, "FF");
		}

		if (courseTable[self].missed >= courseTable[self].limit) {
			strcpy(courseTable[self].gradeLetter, "NA");
			strcpy(courseTable[self].gradeLetterMax, "NA");
			courseTable[self].gradeCur = 0;
			courseTable[self].gradeMax = 0;
		}
		else if (courseTable[self].gradeMax >= 90) {
			strcpy(courseTable[self].gradeLetterMax, "AA");
		}
		else if (courseTable[self].gradeMax >= 85) {
			strcpy(courseTable[self].gradeLetterMax, "BA");
		}
		else if (courseTable[self].gradeMax >= 80) {
			strcpy(courseTable[self].gradeLetterMax, "BB");
		}
		else if (courseTable[self].gradeMax >= 75) {
			strcpy(courseTable[self].gradeLetterMax, "CB");
		}
		else if (courseTable[self].gradeMax >= 70) {
			strcpy(courseTable[self].gradeLetterMax, "CC");
		}
		else if (courseTable[self].gradeMax >= 65) {
			strcpy(courseTable[self].gradeLetterMax, "DC");
		}
		else if (courseTable[self].gradeMax >= 60) {
			strcpy(courseTable[self].gradeLetterMax, "DD");
		}
		else if (courseTable[self].gradeMax >= 50) {
			strcpy(courseTable[self].gradeLetterMax, "FD");
		}
		else {
			strcpy(courseTable[self].gradeLetterMax, "FF");
		}
	}
	else {
		if (courseTable[self].missed >= courseTable[self].limit) {
			strcpy(courseTable[self].gradeLetter, "NA");
			strcpy(courseTable[self].gradeLetterMax, "NA");
			courseTable[self].gradeCur = 0;
			courseTable[self].gradeMax = 0;
		}
		else if (courseTable[self].gradeCur >= 60) {
			strcpy(courseTable[self].gradeLetter, "S");
		}
		else {
			strcpy(courseTable[self].gradeLetter, "U");
		}
	}
}


void UpdateGPA(struct course *courseTable, float *gpa, float *gpaMax, int courseCount)
{
	int i, totalCredit = 0;
	float raw = 0, courseGrade, res;
	for (i = 0; i < courseCount; i++) {
		if (strcmp(courseTable[i].gradeLetter, "AA") == 0) {
			courseGrade = 4.00;
		}else if (strcmp(courseTable[i].gradeLetter, "BA") == 0) {
			courseGrade = 3.50;
		}else if (strcmp(courseTable[i].gradeLetter, "BB") == 0) {
			courseGrade = 3.00;
		}else if (strcmp(courseTable[i].gradeLetter, "CB") == 0) {
			courseGrade = 2.50;
		}else if (strcmp(courseTable[i].gradeLetter, "CC") == 0) {
			courseGrade = 2.00;
		}else if (strcmp(courseTable[i].gradeLetter, "DC") == 0) {
			courseGrade = 1.50;
		}else if (strcmp(courseTable[i].gradeLetter, "DD") == 0) {
			courseGrade = 1.00;
		}else if (strcmp(courseTable[i].gradeLetter, "FD") == 0) {
			courseGrade = 0.50;
		}else{
			courseGrade = 0;
		}
		totalCredit += courseTable[i].credit;
		raw += courseTable[i].credit * courseGrade;
	}
	res = raw / totalCredit;
	*gpa = res;

	raw = 0;
	for (i = 0; i < courseCount; i++) {
		if (strcmp(courseTable[i].gradeLetterMax, "AA") == 0) {
			courseGrade = 4.00;
		}else if (strcmp(courseTable[i].gradeLetterMax, "BA") == 0) {
			courseGrade = 3.50;
		}else if (strcmp(courseTable[i].gradeLetterMax, "BB") == 0) {
			courseGrade = 3.00;
		}else if (strcmp(courseTable[i].gradeLetterMax, "CB") == 0) {
			courseGrade = 2.50;
		}else if (strcmp(courseTable[i].gradeLetterMax, "CC") == 0) {
			courseGrade = 2.00;
		}else if (strcmp(courseTable[i].gradeLetterMax, "DC") == 0) {
			courseGrade = 1.50;
		}else if (strcmp(courseTable[i].gradeLetterMax, "DD") == 0) {
			courseGrade = 1.00;
		}else if (strcmp(courseTable[i].gradeLetterMax, "FD") == 0) {
			courseGrade = 0.50;
		}else {
			courseGrade = 0;
		}
		raw += courseTable[i].credit * courseGrade;
	}
	res = raw / totalCredit;
	*gpaMax = res;
}


void AddGrade(struct course *courseTable, int self)
{
	system("CLS");
	int adding = 1;
	char tempChar;
	while (adding) {
		printf("Enter exam name: ");
		scanf("%[^\n]s", courseTable[self].grades[courseTable[self].gradeCount].name);

		while (tempChar = getchar() != '\n' && tempChar != EOF) { tempChar = getchar; }
		printf("Enter grade: ");
		scanf("%d", &courseTable[self].grades[courseTable[self].gradeCount].value);
		
		printf("Enter weight (without percentage mark): ");
		scanf("%d", &courseTable[self].grades[courseTable[self].gradeCount].weight);

		while (tempChar = getchar() != '\n' && tempChar != EOF) { tempChar = getchar; }
		printf("Enter date: ");
		scanf("%[^\n]s", courseTable[self].grades[courseTable[self].gradeCount].date);

		while (tempChar = getchar() != '\n' && tempChar != EOF) { tempChar = getchar; }
		printf("Enter class: ");
		scanf("%[^\n]s", courseTable[self].grades[courseTable[self].gradeCount].classroom);
		
		
		printf("Succsessfuly added!\n");	courseTable[self].gradeCount += 1;
		while (tempChar = getchar() != '\n' && tempChar != EOF) {}
		while (1){
			printf("Do you want to add more? (y/n): ");
			if (((tempChar = getchar()) == 'n' || tempChar == 'N') && courseTable[self].gradeCount < 12) {
				adding = 0;
				break;
			}else if (tempChar == 'y' || tempChar == 'Y') {
				break;
			}
			while (tempChar = getchar() != '\n' && tempChar != EOF) {}
		}
			
	}
	UpdateIntegerGrading(courseTable, self);
	UpdateLetterGrading(courseTable, self);
}

void RemoveGarde(struct course *courseTable, int self) 
{
	struct grade copyGrades[12];
	int index, i;
	printf("Which exam to remove: ");
	scanf("%d", &index);
	int moveCount = courseTable[self].gradeCount - index, j = index;
	for (i = 0; i < moveCount; i++) {
		strcpy(copyGrades[i].name, courseTable[self].grades[j].name);
		strcpy(copyGrades[i].date, courseTable[self].grades[j].date);
		strcpy(copyGrades[i].classroom, courseTable[self].grades[j].classroom);
		copyGrades[i].value = courseTable[self].grades[j].value;
		copyGrades[i].weight = courseTable[self].grades[j].weight;
		j++;
	}
	i = 0;
	for (j = index - 1; j < moveCount; j++) {
		strcpy(courseTable[self].grades[j].name, copyGrades[i].name);
		strcpy(courseTable[self].grades[j].date, copyGrades[i].date);
		strcpy(courseTable[self].grades[j].classroom, copyGrades[i].classroom);
		courseTable[self].grades[j].value = copyGrades[i].value;
		courseTable[self].grades[j].weight = copyGrades[i].weight;
		i++;
	}
	courseTable[self].gradeCount -= 1;
	UpdateIntegerGrading(courseTable, self);
	UpdateLetterGrading(courseTable, self);
}

void EditGrade(struct course *courseTable, int self)
{
	char tempStr[20], check[3] = "-1", tempChar;
	int temp, gradeIndex;
	printf("Which grade: ");
	scanf("%d", &gradeIndex);
	gradeIndex--;
	system("CLS");
	printf("Enter -1 to make no change");
	printf("\nName(%s): ", courseTable[self].grades[gradeIndex].name);
	while (tempChar = getchar() != '\n' && tempChar != EOF) { tempChar = getchar; }
	scanf("%[^\n]s", tempStr);
	if (strcmp(check, tempStr) != 0) {
		strcpy(courseTable[self].grades[gradeIndex].name, tempStr);
	}
	system("CLS");
	printf("Enter -1 to make no change");
	printf("\nDate(%s): ", courseTable[self].grades[gradeIndex].date);
	while (tempChar = getchar() != '\n' && tempChar != EOF) { tempChar = getchar; }
	scanf("%[^\n]s", tempStr);
	if (strcmp(check, tempStr) != 0) {
		strcpy(courseTable[self].grades[gradeIndex].date, tempStr);
	}
	system("CLS");
	printf("Enter -1 to make no change");
	printf("\nClassroom(%s): ", courseTable[self].grades[gradeIndex].classroom);
	while (tempChar = getchar() != '\n' && tempChar != EOF) { tempChar = getchar; }
	scanf("%[^\n]s", tempStr);
	if (strcmp(check, tempStr) != 0) {
		strcpy(courseTable[self].grades[gradeIndex].classroom, tempStr);
	}
	system("CLS");
	printf("Enter -1 to make no change");
	printf("\nGrade(%d): ", courseTable[self].grades[gradeIndex].value);
	scanf("%d", &temp);
	if (temp != -1) {
		courseTable[self].grades[gradeIndex].value = temp;
	}	
	system("CLS");
	printf("Enter -1 to make no change");
	printf("\nWeight(%d): ", courseTable[self].grades[gradeIndex].weight);
	scanf("%d", &temp);
	if (temp != -1) {
		courseTable[self].grades[gradeIndex].weight = temp;
	}
	UpdateIntegerGrading(courseTable, self);
	UpdateLetterGrading(courseTable, self);
}


void AddNote(struct course *courseTable, int index)
{
	system("CLS");
	char temp[256];
	printf("Enter your note: ");
	scanf("%[^\n]s", courseTable[index].notes[courseTable[index].noteCount].note);
	courseTable[index].noteCount += 1;


}

void RemoveNote(struct course *courseTable, int self) 
{
	struct note copyNotes[24];
	int index, i ;
	printf("Which note to remove: ");
	scanf("%d", &index);
	int moveCount = courseTable[self].noteCount - index, j = index;
	for (i = 0; i < moveCount; i++) {
		strcpy(copyNotes[i].note, courseTable[self].notes[j].note);
		j++;
	}
	i = 0;
	for (j = index - 1; j < moveCount; j++) {
		strcpy(courseTable[self].notes[j].note, copyNotes[i].note);
		i++;
	}
	courseTable[self].noteCount -= 1;
}


void AddCourse(struct course *courseTable, int *self)
{
	int adding = 1, percentage;
	char tempChar, tempChar2;
	while (adding) {
		printf("Enter course name: ");
		scanf("%[^\n]s", courseTable[*self].name);
		
		while (tempChar = getchar() != '\n' && tempChar != EOF) { tempChar = getchar; }
		printf("Enter hours per week: ");
		scanf("%d", &courseTable[*self].weeklyHours);

		printf("Enter course credit: ");
		scanf("%d", &courseTable[*self].credit);

		
		while (tempChar = getchar() != '\n' && tempChar != EOF) { tempChar = getchar; }
		printf("Enter the limit either in percentage (%%x) or hours (x): ");
		if ( (tempChar = getchar()) == '%' ) {
			scanf("%d", &percentage);
			courseTable[*self].limit = (courseTable[*self].weeklyHours * (100-percentage) * 14) / 100;
		}else {
			if((tempChar2 = getchar()) != '\n'){
			courseTable[*self].limit = ((tempChar - '0')*10) + (tempChar2 - '0');
			}else {
				courseTable[*self].limit = tempChar - '0';
			}
		}

		courseTable[*self].missed = 0; courseTable[*self].noteCount = 0; courseTable[*self].gradeCount = 0;
		courseTable[*self].gradeCur = 0; courseTable[*self].gradeMax = 0; strcpy(courseTable[*self].gradeLetter, "FF"); strcpy(courseTable[*self].gradeLetterMax ,"AA");
		*self = *self + 1;
		printf("Succsessfuly added!\n");
		while (1) {
			while (tempChar = getchar() != '\n' && tempChar != EOF) {}
			printf("Do you want to add more? (y/n): ");
			if ((tempChar = getchar()) == 'n' || tempChar == 'N') {
				adding = 0;
				break;
			}else if (tempChar == 'y' || tempChar == 'Y') {
				break;
			}
		}
		while (tempChar = getchar() != '\n' && tempChar != EOF) {}
	}
}


void RemoveCourse(struct course *courseTable, int self, int *size) 
{
	struct course *copyTable;
	int i, moveCount = *size - self, j = self, k;
	copyTable = (struct course *) malloc(sizeof(struct course)*moveCount);
	for (i = 0; i < moveCount; i++) {
		strcpy(copyTable[i].name, courseTable[j].name);
		copyTable[i].limit = courseTable[j].limit;
		copyTable[i].missed = courseTable[j].missed;
		copyTable[i].weeklyHours = courseTable[j].weeklyHours; 
		copyTable[i].noteCount = courseTable[j].noteCount;
		copyTable[i].gradeCount = courseTable[j].gradeCount;
		copyTable[i].credit = courseTable[j].credit;
		copyTable[i].gradeCur = copyTable[j].gradeCur;
		copyTable[i].gradeMax = copyTable[j].gradeMax;
		strcpy(copyTable[i].gradeLetter, courseTable[j].gradeLetter);
		strcpy(copyTable[i].gradeLetterMax, courseTable[j].gradeLetterMax);
		for (k = 0; k < courseTable[j].noteCount; k++) {
			strcpy(copyTable[i].notes[k].note, courseTable[j].notes[k].note);

		}
		for (k = 0; k < courseTable[j].gradeCount; k++) {
			strcpy(copyTable[i].grades[k].name, courseTable[j].grades[k].name);
			strcpy(copyTable[i].grades[k].date, courseTable[j].grades[k].date);
			strcpy(copyTable[i].grades[k].classroom, courseTable[j].grades[k].classroom);
			copyTable[i].grades[k].value = courseTable[j].grades[k].value;
			copyTable[i].grades[k].weight = courseTable[j].grades[k].weight;
		}
		j++;
	}
	i = 0;
	for (j = self - 1; j < *size; j++) {
		strcpy(courseTable[j].name, copyTable[i].name);
		courseTable[j].limit  = copyTable[i].limit;
		courseTable[j].missed = copyTable[i].missed;
		courseTable[j].weeklyHours = copyTable[i].weeklyHours;
		courseTable[j].noteCount = copyTable[i].noteCount;
		courseTable[j].gradeCount = copyTable[i].gradeCount;
		courseTable[j].credit = copyTable[i].credit;
		courseTable[j].gradeCur = copyTable[i].gradeCur;
		courseTable[j].gradeMax = copyTable[i].gradeMax;
		strcpy(courseTable[j].gradeLetter, copyTable[i].gradeLetter);
		strcpy(courseTable[j].gradeLetterMax, copyTable[i].gradeLetterMax);
		for (k = 0; k < courseTable[i].noteCount; k++) {
			strcpy(courseTable[j].notes[k].note,copyTable[i].notes[k].note);
		}
		for (k = 0; k < courseTable[i].gradeCount; k++) {
			strcpy(courseTable[j].grades[k].name, copyTable[i].grades[k].name);
			strcpy(courseTable[j].grades[k].date, copyTable[i].grades[k].date);
			strcpy(courseTable[j].grades[k].classroom, copyTable[i].grades[k].classroom);
			courseTable[j].grades[k].value = copyTable[i].grades[k].value;
			courseTable[j].grades[k].weight = copyTable[i].grades[k].weight;
		}
		i++;
	}
	*size -= 1;
}

void RearrangeCourse(struct course *courseTable)
{
	struct course temp;
	int k, to , from;
	printf("To where: ");
	scanf("%d", &to);
	printf("From where: ");
	scanf("%d", &from);
	to--;
	from--;

	strcpy(temp.name, courseTable[to].name);
	temp.limit = courseTable[to].limit;
	temp.missed = courseTable[to].missed;
	temp.weeklyHours = courseTable[to].weeklyHours;
	temp.noteCount = courseTable[to].noteCount;
	temp.gradeCount = courseTable[to].gradeCount;
	temp.credit = courseTable[to].credit;
	temp.gradeCur = courseTable[to].gradeCur;
	temp.gradeMax = courseTable[to].gradeMax;
	strcpy(temp.gradeLetter, courseTable[to].gradeLetter);
	strcpy(temp.gradeLetterMax, courseTable[to].gradeLetterMax);
	for (k = 0; k < courseTable[to].noteCount; k++) {
		strcpy(temp.notes[k].note, courseTable[to].notes[k].note);

	}
	for (k = 0; k < courseTable[to].gradeCount; k++) {
		strcpy(temp.grades[k].name, courseTable[to].grades[k].name);
		strcpy(temp.grades[k].date, courseTable[to].grades[k].date);
		strcpy(temp.grades[k].classroom, courseTable[to].grades[k].classroom);
		temp.grades[k].value = courseTable[to].grades[k].value;
		temp.grades[k].weight = courseTable[to].grades[k].weight;
	}

	strcpy(courseTable[to].name, courseTable[from].name);
	courseTable[to].limit = courseTable[from].limit;
	courseTable[to].missed = courseTable[from].missed;
	courseTable[to].weeklyHours = courseTable[from].weeklyHours;
	courseTable[to].noteCount = courseTable[from].noteCount;
	courseTable[to].gradeCount = courseTable[from].gradeCount;
	courseTable[to].credit = courseTable[from].credit;
	courseTable[to].gradeCur = courseTable[from].gradeCur;
	courseTable[to].gradeMax = courseTable[from].gradeMax;
	strcpy(courseTable[to].gradeLetter, courseTable[from].gradeLetter);
	strcpy(courseTable[to].gradeLetterMax, courseTable[from].gradeLetterMax);
	for (k = 0; k < courseTable[from].noteCount; k++) {
		strcpy(courseTable[to].notes[k].note, courseTable[from].notes[k].note);

	}
	for (k = 0; k < courseTable[from].gradeCount; k++) {
		strcpy(courseTable[to].grades[k].name, courseTable[from].grades[k].name);
		strcpy(courseTable[to].grades[k].date, courseTable[from].grades[k].date);
		strcpy(courseTable[to].grades[k].classroom, courseTable[from].grades[k].classroom);
		courseTable[to].grades[k].value = courseTable[from].grades[k].value;
		courseTable[to].grades[k].weight = courseTable[from].grades[k].weight;
	}

	strcpy(courseTable[from].name, temp.name);
	courseTable[from].limit = temp.limit;
	courseTable[from].missed = temp.missed;
	courseTable[from].weeklyHours = temp.weeklyHours;
	courseTable[from].noteCount = temp.noteCount;
	courseTable[from].gradeCount = temp.gradeCount;
	courseTable[from].credit = temp.credit;
	courseTable[from].gradeCur = temp.gradeCur;
	courseTable[from].gradeMax = temp.gradeMax;
	strcpy(courseTable[from].gradeLetter, temp.gradeLetter);
	strcpy(courseTable[from].gradeLetterMax, temp.gradeLetterMax);
	for (k = 0; k < temp.noteCount; k++) {
		strcpy(courseTable[from].notes[k].note, temp.notes[k].note);

	}
	for (k = 0; k < temp.gradeCount; k++) {
		strcpy(courseTable[from].grades[k].name, temp.grades[k].name);
		strcpy(courseTable[from].grades[k].date, temp.grades[k].date);
		strcpy(courseTable[from].grades[k].classroom, temp.grades[k].classroom);
		courseTable[from].grades[k].value = temp.grades[k].value;
		courseTable[from].grades[k].weight = temp.grades[k].weight;
	}


}


void DisplayBar(int x, int y)
{
	int caseNumber = y / 5;

	if (x <= caseNumber) {
		printf(" ##________\n");
	}
	else if (x <= caseNumber * 2) {
		printf(" ####______\n");
	}
	else if (x <= caseNumber * 3) {
		printf(" ######____\n");
	}
	else if (x <= caseNumber * 4) {
		printf(" ########__\n");
	}
	else if (x <= caseNumber * 5) {
		printf(" ##########\n");
	}
	else {
		printf(" ##########\n");
	}
}


void DisplayGrades(struct course *courseTable, int self)
{
	int i;
	printf("\n==Grades: \n");
	for (i = 0; i < courseTable[self].gradeCount; i++) {
		printf("=%d: %10s => Grade: %3d |Weight: %3d |Date: %16s |Class: %6s\n", i + 1, courseTable[self].grades[i].name, courseTable[self].grades[i].value, courseTable[self].grades[i].weight, courseTable[self].grades[i].date
			, courseTable[self].grades[i].classroom);
	}

}


void DisplayNotes(struct course *courseTable, int self)
{
	int i;
	printf("\n==Notes:\n");
	for (i = 0; i < courseTable[self].noteCount; i++) {
		printf("=%d: %s\n", i + 1, courseTable[self].notes[i].note);
	}
}


void DisplayCurrentGrade(struct course *courseTable, int self)
{
	int i, score = 0;
	for (i = 0; i < courseTable[self].gradeCount; i++) {
		score += courseTable[self].grades[i].value * courseTable[self].grades[i].weight / 100;
	}
	courseTable[self].gradeCur = score;
}





void DisplayAdv(struct course *courseTable, int *courseCount, int self) 
{
	system("CLS");
	int i;
	printf("%d- %-10s", self + 1, courseTable[self].name);
	printf("Grade: ");
	printf(" %3d / %-6s", courseTable[self].gradeCur, courseTable[self].gradeLetter);
	printf("Max: ");
	printf(" %3d / %-6s", courseTable[self].gradeMax, courseTable[self].gradeLetterMax);
	printf("Missed:%d/%d", courseTable[self].missed, courseTable[self].limit);
	DisplayBar(courseTable[self].missed, courseTable[self].limit);
	DisplayGrades(courseTable, self);
	DisplayNotes(courseTable, self);

	printf("\n-b : Back  -m: Add missing  -rm : Remove missing -r : Remove  -an : Add note\n"
		"-rn : Remove note  -ax : Add exam  -rx: Remove exam  -ex Edit exam\n");
}


void AddMissing(struct course *courseTable, int index)
{
	courseTable[index].missed += 1;
	UpdateIntegerGrading(courseTable, index);
	UpdateLetterGrading(courseTable, index);
}

void RemoveMissing(struct course *courseTable, int index)
{
	courseTable[index].missed -= 1;
	UpdateIntegerGrading(courseTable, index);
	UpdateLetterGrading(courseTable, index);
}


void DisplayHome(struct course *courseTable, int *courseCount, float *gpa, int op)
{
	int i;
	UpdateGPA(courseTable, &gpa[0], &gpa[1], *courseCount);
	system("CLS");
	switch (op)	
	{
	case 1:
		for (i = 0; i < *courseCount; i++) {
			printf("%d- %-10s ", i + 1, courseTable[i].name);
			printf("Grade: ");
			printf(" %3d / %-6s", courseTable[i].gradeCur, courseTable[i].gradeLetter);
			DisplayCurrentGrade(courseTable, i);
			printf("Missed:%d/%d", courseTable[i].missed, courseTable[i].limit);
			DisplayBar(courseTable[i].missed, courseTable[i].limit);
			printf("\n");
		}
		printf("GPA: %.2f    MaxGPA: %.2f\n\n", gpa[0], gpa[1]);
		printf("Saved!\n");
		printf("-q : Quit  -!q: Quit without saving  -s : Save  -a : Add  List number : Adv\n");
		break;
	default:
		for (i = 0; i < *courseCount; i++) {
			printf("%d- %-10s ", i + 1, courseTable[i].name);
			printf("Grade: ");
			printf(" %3d / %-6s", courseTable[i].gradeCur, courseTable[i].gradeLetter);
			DisplayCurrentGrade(courseTable, i);
			printf("Missed:%2d/%-4d", courseTable[i].missed, courseTable[i].limit);
			DisplayBar(courseTable[i].missed, courseTable[i].limit);
			printf("\n");
		}
		printf("GPA: %.2f    MaxGPA: %.2f\n\n", gpa[0], gpa[1]);
		printf("-q : Quit  -!q: Quit without saving  -s : Save  -a : Add  List number : Adv\n" 
			"-m : Move\n");
		break;
	}
}


void SaveCourseTable(struct course *courseTable, int courseCount)
{
	FILE *dataStream;
	int i, j;
	dataStream = fopen("data.txt", "w");
	for (i = 0; i < courseCount; i++) {
		j = 0;
		fprintf(dataStream, "%s;%d;%d;%d;%d", courseTable[i].name, courseTable[i].missed, courseTable[i].limit, courseTable[i].credit ,courseTable[i].noteCount);
		while (j < courseTable[i].noteCount) {
			fprintf(dataStream, ";%s", courseTable[i].notes[j].note);
			j++;
		}
		fprintf(dataStream, ";%d;%d", courseTable[i].weeklyHours, courseTable[i].gradeCount);
		j = 0;
		while (j < courseTable[i].gradeCount) {
			fprintf(dataStream, ";%s;%s;%s", courseTable[i].grades[j].name, courseTable[i].grades[j].date, courseTable[i].grades[j].classroom);
			fprintf(dataStream, ";%d;%d", courseTable[i].grades[j].value, courseTable[i].grades[j].weight);
			j++;
		}
		
		fprintf(dataStream, ";%d;%d", courseTable[i].gradeCur, courseTable[i].gradeMax);
		fprintf(dataStream, ";%s;%s", courseTable[i].gradeLetter, courseTable[i].gradeLetterMax);

		if (i != courseCount - 1) {
			fprintf(dataStream,"\n");
		}
	}
	printf("Saved!");
	fclose(dataStream);
}


void DataSize(int *size)
{
	FILE *dataStream;
	char tempChar;
	dataStream = fopen("data.txt", "r");
	tempChar = fgetc(dataStream);
	while (tempChar != EOF) {
		tempChar = fgetc(dataStream);
		*size = *size + 1;
		while (tempChar != '\n' && tempChar != EOF) {
			tempChar = fgetc(dataStream);
		}
	}
	fclose(dataStream);
}


void LoadData(struct course *courseTable, int *courseCount) 
{
	FILE *dataStream;
	DataSize(courseCount);
	int i, j;
	dataStream = fopen("data.txt", "r");

	for (i = 0; i < *courseCount; i++) {
		j = 0;
		fscanf(dataStream, "%[^;]s", courseTable[i].name);
		fscanf(dataStream, ";%d;%d;%d;%d", &courseTable[i].missed, &courseTable[i].limit, &courseTable[i].credit, &courseTable[i].noteCount);
		while (j < courseTable[i].noteCount) {
			fgetc(dataStream);
			fscanf(dataStream, "%[^;]s", courseTable[i].notes[j].note);
			j++;
		}
		fscanf(dataStream, ";%d;%d", &courseTable[i].weeklyHours, &courseTable[i].gradeCount);
		j = 0;
		while (j < courseTable[i].gradeCount) {
			fgetc(dataStream);
			fscanf(dataStream, "%[^;]s", courseTable[i].grades[j].name);
			fgetc(dataStream);
			fscanf(dataStream, "%[^;]s", courseTable[i].grades[j].date);
			fgetc(dataStream);
			fscanf(dataStream, "%[^;]s", courseTable[i].grades[j].classroom);
			fscanf(dataStream, ";%d;%d", &courseTable[i].grades[j].value, &courseTable[i].grades[j].weight);
			j++;
		}
		fscanf(dataStream, ";%d;%d", &courseTable[i].gradeCur, &courseTable[i].gradeMax);
		fgetc(dataStream);
		fscanf(dataStream, "%[^;]s", courseTable[i].gradeLetter);
		fgetc(dataStream);
		fscanf(dataStream, "%[^\n]s", courseTable[i].gradeLetterMax);

		fgetc(dataStream);
	}

	fclose(dataStream);
}


void saveGpa(float *gpa) 
{
	FILE *dataSteam;
	dataSteam = fopen("gpa.txt", "w");
	fprintf(dataSteam, "%.2f;%.2f", gpa[0], gpa[1]);
	fclose(dataSteam);
}

void loadGpa(float *gpa)
{
	FILE *dataSteam;
	dataSteam = fopen("gpa.txt", "r");
	fscanf(dataSteam, "%.2f;%.2f", gpa[0], gpa[1]);
	fclose(dataSteam);
}


int main()
{
	FILE *dataStream;
	struct course *courseTable;
	courseTable = (struct course *) malloc(sizeof(struct course) * 15);

	int i, courseCount = 0, homeLoop = 1, userChoice, advLoop = 1, courseToRemove, self;
	float gpa[2];
	gpa[0] = 0; gpa[1] = 0;
	char userInput[5], tempChar;
	if (FirstTimeSetupCheck()) {
		courseCount = 0;
		printf("You have no courses. Add some !\n");
		AddCourse(courseTable, &courseCount);
	}else {
		LoadData(courseTable, &courseCount);
		loadGpa(&gpa);
	}
	
	
	
	while (homeLoop) {
		DisplayHome(courseTable, &courseCount, &gpa, 0);
		scanf("%s", userInput);
		while (tempChar = getchar() != '\n' && tempChar != EOF) {}
		if (strcmp(userInput, "-a") == 0) {
			//add course
			AddCourse(courseTable, &courseCount);
			DisplayHome(courseTable, &courseCount, &gpa, 0);
		}else if (strcmp(userInput, "-s") == 0) {
			//save
			SaveCourseTable(courseTable, courseCount);
			saveGpa(gpa);
			DisplayHome(courseTable, &courseCount, &gpa, 1);
		}else if (strcmp(userInput, "-q") == 0) {
			//save and quit
			SaveCourseTable(courseTable, courseCount);
			saveGpa(gpa);
			return 0;
		}else if (strcmp(userInput, "-!q") == 0) {
			//quit without saving
			return 0;
		}
		else if (strcmp(userInput, "-m") == 0) {
			RearrangeCourse(courseTable);
			DisplayHome(courseTable, &courseCount, &gpa, 1);
		}else if (strcmp(userInput, "-r") == 0) {
			//remove course
			printf("Which course: ");
			scanf("%d", &courseToRemove);
			RemoveCourse(courseTable, courseToRemove, &courseCount);
		}else {
			if (userInput[1] != '\n' && userInput[1] != '\0') {
				userChoice = ((userInput[0] - '0') * 10) + (userInput[1] - '0');
			}
			else {
				userChoice = userInput[0] - '0';
			}
			DisplayAdv(courseTable, &courseCount, userChoice-1);
			while (advLoop) {
				scanf("%s", userInput);
				if (strcmp(userInput, "-b") == 0) {
					break;
				}else if (strcmp(userInput, "-m") == 0) {
					AddMissing(courseTable, userChoice-1);
					DisplayAdv(courseTable, &courseCount, userChoice-1);
				}else if (strcmp(userInput, "-rm") == 0) {
					RemoveMissing(courseTable, userChoice - 1);
					DisplayAdv(courseTable, &courseCount, userChoice - 1);
				}
				else if (strcmp(userInput, "-r") == 0) {
					RemoveCourse(courseTable, userChoice, &courseCount);
					break;
				}else if (strcmp(userInput, "-an") == 0) {
					if (courseTable[userChoice].noteCount <= 12) {
						while (tempChar = getchar() != '\n' && tempChar != EOF) {}
						AddNote(courseTable, userChoice-1);
						DisplayAdv(courseTable, &courseCount, userChoice - 1);
					}else {
						printf("\nNote limit reached please remove notes to add more.\n");
						DisplayAdv(courseTable, &courseCount, userChoice - 1);
					}
				}else if (strcmp(userInput, "-rn") == 0) {
					while (tempChar = getchar() != '\n' && tempChar != EOF) {}
					RemoveNote(courseTable, userChoice-1);
					DisplayAdv(courseTable, &courseCount, userChoice - 1);
				}else if (strcmp(userInput, "-ax") == 0) {
					while (tempChar = getchar() != '\n' && tempChar != EOF) {}
					AddGrade(courseTable, userChoice - 1);
					DisplayAdv(courseTable, &courseCount, userChoice - 1);
				}else if (strcmp(userInput, "-rx") == 0) {
					while (tempChar = getchar() != '\n' && tempChar != EOF) {}
					RemoveGarde(courseTable, userChoice - 1);
					DisplayAdv(courseTable, &courseCount, userChoice - 1);
				}else if (strcmp(userInput, "-ex") == 0){
					while (tempChar = getchar() != '\n' && tempChar != EOF) {}
					EditGrade(courseTable, userChoice - 1);
					DisplayAdv(courseTable, &courseCount, userChoice - 1);
				}
			}
		}
	}



	while (1) {
		continue;
	}
	return 0;
}