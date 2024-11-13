//�ӤH�ɮפ��� {	�̭]����(vaccine)*5 ���絲�G(test)*100	}

#include <stdio.h>
#include <string.h>

//�̭]����
struct vaccine
{
	int number;	//�ĴX��
	char date[9];	//���ؤ��
	char brand[20];	//�̭]�~�P
	char hospital[30];	//������|
};

//���絲�G
struct test
{
	char date[9];	//������
	char brand[20];	//�������
	char place[30];	//����a�I
	int result;	//���絲�G
};

//�T�E�H�����
struct diagnosed
{
	char id[11];	//�����Ҹ�
	char date[9];	//�T�E�ɶ�
};

void vac();	//�s�W�̭]���ظ�T (�̭]���� vaccination)
void res();	//�s�W���絲�G��T (���絲�G test result)
void personal();	//�d�߭ӤH��T
void prt_all();	//��ܩҦ��T�E�H��
void del();	//�R���T�E�H��

int main()
{
	int choise = 0;	//�\��

	while (choise != -1)
	{
		printf("\n�п�ܥ\�� 1)�s�W�̭]���ظ�T 2)�s�W���絲�G��T 3)�d�߭ӤH��T 4)��ܩҦ��T�E�H�� 5)�R���T�E�H�� -1)���� : ");
		scanf("%d", &choise);

		switch (choise)
		{
		case 1:
			vac();
			break;
		case 2:
			res();
			break;
		case 3:
			personal();
			break;
		case 4:
			prt_all();
			break;
		case 5:
			del();
			break;
		case -1:
			break;
		default:
			printf("��J���~!�Э��s��J�C\n");
			break;
		}
	}

	return 0;
}

//�s�W�̭]���ظ�T
void vac()
{
	char filename[15] = { "          .dat" };
	char id[11];	//�����Ҹ�
	vaccine nvac[5];
	test ntest[100];

	//��l��
	for (int i = 0; i < 5; i++)
	{
		nvac[i] = { 0," "," "," " };
	}
	for (int i = 0; i < 100; i++)
	{
		ntest[i] = { " ", " ", " ", 0 };
	}

	//��Jid
	printf("�п�J�����Ҹ�: ");
	scanf("%s", id);

	//�N�����Ҹ��ƻs���ɦW
	for (int i = 0; i < 10; i++)
	{
		filename[i] = id[i];
	}

	FILE* people; /*people;*/	//�ӤH�ɮ�
	if ((people = fopen(filename, "rb+")) == NULL)	//�}�ɥ���
	{
		people = fopen(filename, "wb+");

		//��J��l�Ƹ��
		fwrite(nvac, sizeof(struct vaccine), 5, people);
		fwrite(ntest, sizeof(struct test), 100, people);
	}
	else
	{
		//Ū�����ظ��
		fread(nvac, sizeof(struct vaccine), 5, people);
	}
	for (int i = 0; i < 5; i++)
	{
		if (nvac[i].number==0)
		{
			//��J���ظ��
			printf("�п�J���� �ĴX�� : ");
			scanf("%d", &nvac[i].number);
			while (nvac[i].number<=0)
			{
				printf("��J���~!�Э��s��J : ");
				scanf("%d", &nvac[i].number);
			}
			printf("�п�J ���ؤ�� : ");
			scanf("%s", nvac[i].date);
			printf("�п�J �̭]�~�P : ");
			scanf("%s", nvac[i].brand);
			printf("�п�J ������| : ");
			scanf("%s", nvac[i].hospital);

			//�������ظ��
			fseek(people, i * sizeof(struct vaccine), SEEK_SET);
			fwrite(&nvac[i], sizeof(struct vaccine), 1, people);

			break;
		}
	}

	fclose(people);
}

//�s�W���絲�G��T
void res() 
{
	char filename[15] = { "          .dat" };
	char id[11];	//�����Ҹ�
	vaccine nvac[5];
	test ntest[100];
	diagnosed sure[10000];

	//��l��
	for (int i = 0; i < 5; i++)
	{
		nvac[i] = { 0," "," "," " };
	}
	for (int i = 0; i < 100; i++)
	{
		ntest[i] = { " ", " ", " ", 0 };
	}
	for (int i = 0; i < 10000; i++)
	{
		sure[i] = { " " , " " };
	}

	//��Jid
	printf("�п�J�����Ҹ�: ");
	scanf("%s", id);

	//�N�����Ҹ��ƻs���ɦW
	for (int i = 0; i < 10; i++)
	{
		filename[i] = id[i];
	}

	FILE* people; /*people;*/	//�ӤH�ɮ�
	if ((people = fopen(filename, "rb+")) == NULL)	//�}�ɥ���
	{
		people = fopen(filename, "wb+");

		//��J��l�Ƹ��
		fwrite(nvac, sizeof(struct vaccine), 5, people);
		fwrite(ntest, sizeof(struct test), 100, people);
	}
	else
	{
		//Ū�����絲�G
		fseek(people, 5 * sizeof(struct vaccine), SEEK_SET);
		fread(&ntest, sizeof(struct test), 100, people);
	}

	for (int i = 0; i < 100; i++)
	{
		if (ntest[i].date[0] == ' ')
		{
			//��J���絲�G
			printf("�п�J ������ : ");
			scanf("%s", ntest[i].date);
			printf("�п�J ������� : ");
			scanf("%s", ntest[i].brand);
			printf("�п�J ����a�I : ");
			scanf("%s", ntest[i].place);
			printf("�п�J ���絲�G 1)���� 2)���� : ");
			scanf("%d", &ntest[i].result);
			while (ntest[i].result != 1 && ntest[i].result != 2)
			{
				printf("��J���~!�Э��s��J : ");
				scanf("%d", &ntest[i].result);
			}

			//�������絲�G
			fseek(people,5*sizeof(struct vaccine)+ i * sizeof(struct test),SEEK_SET);
			fwrite(&ntest[i], sizeof(struct test), 1, people);

			fclose(people);
			
			//�s�W�T�E�H�����
			while (ntest[i].result == 2)
			{
				FILE* list;	//�T�E�W��
				if ((list = fopen("DiagnosedList.dat", "rb+")) == NULL)	//�}�ɥ���
				{
					list = fopen("DiagnosedList.dat", "wb+");

					//��J��l�Ƹ��
					fwrite(sure, sizeof(struct diagnosed), 10000, list);
				}
				else
				{
					//Ū���즳���
					fread(sure, sizeof(struct diagnosed), 10000, list);
				}

				for (int n = 0; n < 10000; n++)
				{
					//�s�W�T�E�H�����
					if (sure[n].id[0] == ' ' )
					{
						//�N �����Ҹ� & �T�E��� �ƻs�� sure[n]
						strcpy(sure[n].id, id);
						strcpy(sure[n].date, ntest[i].date);

						fseek(list, n * sizeof(struct diagnosed), SEEK_SET);
						fwrite(&sure[n], sizeof(struct diagnosed), 1, list);

						break;
					}
				}

				fclose(list);
				break;
			}
			
			break;
		}
	}
}

//�d�߭ӤH��T
void personal()
{
	char filename[15] = { "          .dat" };
	char id[11];	//�����Ҹ�
	vaccine nvac[5]; 
	test ntest[100];

	//��l��
	for (int i = 0; i < 5; i++)
	{
		nvac[i] = { 0," "," "," " };
	}
	for (int i = 0; i < 100; i++)
	{
		ntest[i] = { " ", " ", " ", 0 };
	}

	//��Jid
	printf("�п�J�����Ҹ�: ");
	scanf("%s", id);

	//�N�����Ҹ��ƻs���ɦW
	for (int i = 0; i < 10; i++)
	{
		filename[i] = id[i];
	}

	FILE* people; /*people;*/	//�ӤH�ɮ�
	if ((people = fopen(filename, "rb+")) == NULL)	//�}�ɥ���
	{
		printf("�S�����H���ɮ�!!\n");
	}
	else
	{
		//���ظ��
		printf("���ظ��:\n");
		for (int i = 0; i < 5; i++)
		{
			//Ū�����ظ��
			fread(&nvac[i], sizeof(struct vaccine), 1, people);
			
			//��X���ظ��
			if (nvac[i].number != 0)
			{
				printf("�� %d �� ���ؤ��: %-9s �̭]�~�P: %-20s ������|: %s\n", nvac[i].number, nvac[i].date, nvac[i].brand, nvac[i].hospital);
			}
		}

		//���絲�G
		printf("���絲�G:\n");
		for (int i = 0; i < 100; i++)
		{
			//Ū�����絲�G
			fread(&ntest[i], sizeof(struct test), 1, people);
			
			//��X���絲�G
			if (ntest[i].date[0] != ' ')
			{	
				printf("������: %-9s ����a�I: %-30s �������: %-20s ���絲�G 1)���� 2)����: %d\n", ntest[i].date, ntest[i].brand, ntest[i].place, ntest[i].result);	
			}
		}

		fclose(people);
	}
}

//��ܩҦ��T�E�H��
void prt_all()
{
	diagnosed sure[10000];

	//��l��
	for (int i = 0; i < 10000; i++)
	{
		sure[i] = { " " , " " };
	}

	FILE* list;	//�T�E�W��
	if ((list = fopen("DiagnosedList.dat", "rb+")) == NULL)	//�}�ɥ���
	{
		printf("File coulr not be opened.");
	}
	else
	{
		//Ū���즳���
		rewind(list);
		fread(sure, sizeof(struct diagnosed), 10000, list);

		for (int n = 0; n < 10000; n++)
		{
			//��X�T�E�H�����
			if (sure[n].id[0] != ' ')
			{
				printf("�����Ҹ�: %-11s �T�E�ɶ�: %-9s\n", sure[n].id, sure[n].date);
			}
		}
	}

	fclose(list);
}

//�R���T�E�H��
void del()
{
	char filename[15] = { "          .dat" };
	char id[11];	//�����Ҹ�
	diagnosed personal = { " " , " " };

	//��Jid
	printf("�п�J�����Ҹ�: ");
	scanf("%s", id);

	FILE* list;	//�T�E�W��
	if ((list = fopen("DiagnosedList.dat", "rb+")) == NULL)	//�}�ɥ���
	{
		printf("File coulr not be opened.");
	}
	else
	{
		for (int n = 0; n < 10000; n++)
		{
			//Ū���@�����
			fread(&personal, sizeof(struct diagnosed), 1, list);
			
			//�R���T�E�H�����
			if ((strcmp(personal.id,id))==0)	//��r��ۦP
			{
				fseek(list, n * sizeof(struct diagnosed), SEEK_SET);
				personal = { " "," " };
				fwrite(&personal, sizeof(struct diagnosed), 1, list);
			
				printf("���T�E�H����Ƥw�R��!\n");
				break;
			}
			else if(n==9999)
			{
				printf("�d�L���H���!\n");
			}
		}
	}

	fclose(list);
}