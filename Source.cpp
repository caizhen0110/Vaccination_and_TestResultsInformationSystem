//個人檔案內文 {	疫苗接種(vaccine)*5 檢驗結果(test)*100	}

#include <stdio.h>
#include <string.h>

//疫苗接種
struct vaccine
{
	int number;	//第幾劑
	char date[9];	//接種日期
	char brand[20];	//疫苗品牌
	char hospital[30];	//接種醫院
};

//檢驗結果
struct test
{
	char date[9];	//檢驗日期
	char brand[20];	//檢驗種類
	char place[30];	//檢驗地點
	int result;	//檢驗結果
};

//確診人員資料
struct diagnosed
{
	char id[11];	//身分證號
	char date[9];	//確診時間
};

void vac();	//新增疫苗接種資訊 (疫苗接種 vaccination)
void res();	//新增檢驗結果資訊 (檢驗結果 test result)
void personal();	//查詢個人資訊
void prt_all();	//顯示所有確診人員
void del();	//刪除確診人員

int main()
{
	int choise = 0;	//功能

	while (choise != -1)
	{
		printf("\n請選擇功能 1)新增疫苗接種資訊 2)新增檢驗結果資訊 3)查詢個人資訊 4)顯示所有確診人員 5)刪除確診人員 -1)結束 : ");
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
			printf("輸入錯誤!請重新輸入。\n");
			break;
		}
	}

	return 0;
}

//新增疫苗接種資訊
void vac()
{
	char filename[15] = { "          .dat" };
	char id[11];	//身分證號
	vaccine nvac[5];
	test ntest[100];

	//初始化
	for (int i = 0; i < 5; i++)
	{
		nvac[i] = { 0," "," "," " };
	}
	for (int i = 0; i < 100; i++)
	{
		ntest[i] = { " ", " ", " ", 0 };
	}

	//輸入id
	printf("請輸入身分證號: ");
	scanf("%s", id);

	//將身分證號複製為檔名
	for (int i = 0; i < 10; i++)
	{
		filename[i] = id[i];
	}

	FILE* people; /*people;*/	//個人檔案
	if ((people = fopen(filename, "rb+")) == NULL)	//開檔失敗
	{
		people = fopen(filename, "wb+");

		//輸入初始化資料
		fwrite(nvac, sizeof(struct vaccine), 5, people);
		fwrite(ntest, sizeof(struct test), 100, people);
	}
	else
	{
		//讀取接種資料
		fread(nvac, sizeof(struct vaccine), 5, people);
	}
	for (int i = 0; i < 5; i++)
	{
		if (nvac[i].number==0)
		{
			//輸入接種資料
			printf("請輸入此為 第幾劑 : ");
			scanf("%d", &nvac[i].number);
			while (nvac[i].number<=0)
			{
				printf("輸入錯誤!請重新輸入 : ");
				scanf("%d", &nvac[i].number);
			}
			printf("請輸入 接種日期 : ");
			scanf("%s", nvac[i].date);
			printf("請輸入 疫苗品牌 : ");
			scanf("%s", nvac[i].brand);
			printf("請輸入 接種醫院 : ");
			scanf("%s", nvac[i].hospital);

			//紀錄接種資料
			fseek(people, i * sizeof(struct vaccine), SEEK_SET);
			fwrite(&nvac[i], sizeof(struct vaccine), 1, people);

			break;
		}
	}

	fclose(people);
}

//新增檢驗結果資訊
void res() 
{
	char filename[15] = { "          .dat" };
	char id[11];	//身分證號
	vaccine nvac[5];
	test ntest[100];
	diagnosed sure[10000];

	//初始化
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

	//輸入id
	printf("請輸入身分證號: ");
	scanf("%s", id);

	//將身分證號複製為檔名
	for (int i = 0; i < 10; i++)
	{
		filename[i] = id[i];
	}

	FILE* people; /*people;*/	//個人檔案
	if ((people = fopen(filename, "rb+")) == NULL)	//開檔失敗
	{
		people = fopen(filename, "wb+");

		//輸入初始化資料
		fwrite(nvac, sizeof(struct vaccine), 5, people);
		fwrite(ntest, sizeof(struct test), 100, people);
	}
	else
	{
		//讀取檢驗結果
		fseek(people, 5 * sizeof(struct vaccine), SEEK_SET);
		fread(&ntest, sizeof(struct test), 100, people);
	}

	for (int i = 0; i < 100; i++)
	{
		if (ntest[i].date[0] == ' ')
		{
			//輸入檢驗結果
			printf("請輸入 檢驗日期 : ");
			scanf("%s", ntest[i].date);
			printf("請輸入 檢驗種類 : ");
			scanf("%s", ntest[i].brand);
			printf("請輸入 檢驗地點 : ");
			scanf("%s", ntest[i].place);
			printf("請輸入 檢驗結果 1)陰性 2)陽性 : ");
			scanf("%d", &ntest[i].result);
			while (ntest[i].result != 1 && ntest[i].result != 2)
			{
				printf("輸入錯誤!請重新輸入 : ");
				scanf("%d", &ntest[i].result);
			}

			//紀錄檢驗結果
			fseek(people,5*sizeof(struct vaccine)+ i * sizeof(struct test),SEEK_SET);
			fwrite(&ntest[i], sizeof(struct test), 1, people);

			fclose(people);
			
			//新增確診人員資料
			while (ntest[i].result == 2)
			{
				FILE* list;	//確診名單
				if ((list = fopen("DiagnosedList.dat", "rb+")) == NULL)	//開檔失敗
				{
					list = fopen("DiagnosedList.dat", "wb+");

					//輸入初始化資料
					fwrite(sure, sizeof(struct diagnosed), 10000, list);
				}
				else
				{
					//讀取原有資料
					fread(sure, sizeof(struct diagnosed), 10000, list);
				}

				for (int n = 0; n < 10000; n++)
				{
					//新增確診人員資料
					if (sure[n].id[0] == ' ' )
					{
						//將 身分證號 & 確診日期 複製到 sure[n]
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

//查詢個人資訊
void personal()
{
	char filename[15] = { "          .dat" };
	char id[11];	//身分證號
	vaccine nvac[5]; 
	test ntest[100];

	//初始化
	for (int i = 0; i < 5; i++)
	{
		nvac[i] = { 0," "," "," " };
	}
	for (int i = 0; i < 100; i++)
	{
		ntest[i] = { " ", " ", " ", 0 };
	}

	//輸入id
	printf("請輸入身分證號: ");
	scanf("%s", id);

	//將身分證號複製為檔名
	for (int i = 0; i < 10; i++)
	{
		filename[i] = id[i];
	}

	FILE* people; /*people;*/	//個人檔案
	if ((people = fopen(filename, "rb+")) == NULL)	//開檔失敗
	{
		printf("沒有此人的檔案!!\n");
	}
	else
	{
		//接種資料
		printf("接種資料:\n");
		for (int i = 0; i < 5; i++)
		{
			//讀取接種資料
			fread(&nvac[i], sizeof(struct vaccine), 1, people);
			
			//輸出接種資料
			if (nvac[i].number != 0)
			{
				printf("第 %d 劑 接種日期: %-9s 疫苗品牌: %-20s 接種醫院: %s\n", nvac[i].number, nvac[i].date, nvac[i].brand, nvac[i].hospital);
			}
		}

		//檢驗結果
		printf("檢驗結果:\n");
		for (int i = 0; i < 100; i++)
		{
			//讀取檢驗結果
			fread(&ntest[i], sizeof(struct test), 1, people);
			
			//輸出檢驗結果
			if (ntest[i].date[0] != ' ')
			{	
				printf("檢驗日期: %-9s 檢驗地點: %-30s 檢驗種類: %-20s 檢驗結果 1)陰性 2)陽性: %d\n", ntest[i].date, ntest[i].brand, ntest[i].place, ntest[i].result);	
			}
		}

		fclose(people);
	}
}

//顯示所有確診人員
void prt_all()
{
	diagnosed sure[10000];

	//初始化
	for (int i = 0; i < 10000; i++)
	{
		sure[i] = { " " , " " };
	}

	FILE* list;	//確診名單
	if ((list = fopen("DiagnosedList.dat", "rb+")) == NULL)	//開檔失敗
	{
		printf("File coulr not be opened.");
	}
	else
	{
		//讀取原有資料
		rewind(list);
		fread(sure, sizeof(struct diagnosed), 10000, list);

		for (int n = 0; n < 10000; n++)
		{
			//輸出確診人員資料
			if (sure[n].id[0] != ' ')
			{
				printf("身分證號: %-11s 確診時間: %-9s\n", sure[n].id, sure[n].date);
			}
		}
	}

	fclose(list);
}

//刪除確診人員
void del()
{
	char filename[15] = { "          .dat" };
	char id[11];	//身分證號
	diagnosed personal = { " " , " " };

	//輸入id
	printf("請輸入身分證號: ");
	scanf("%s", id);

	FILE* list;	//確診名單
	if ((list = fopen("DiagnosedList.dat", "rb+")) == NULL)	//開檔失敗
	{
		printf("File coulr not be opened.");
	}
	else
	{
		for (int n = 0; n < 10000; n++)
		{
			//讀取一筆資料
			fread(&personal, sizeof(struct diagnosed), 1, list);
			
			//刪除確診人員資料
			if ((strcmp(personal.id,id))==0)	//兩字串相同
			{
				fseek(list, n * sizeof(struct diagnosed), SEEK_SET);
				personal = { " "," " };
				fwrite(&personal, sizeof(struct diagnosed), 1, list);
			
				printf("此確診人員資料已刪除!\n");
				break;
			}
			else if(n==9999)
			{
				printf("查無此人資料!\n");
			}
		}
	}

	fclose(list);
}