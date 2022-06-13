#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//������ϵ�˽ṹ��
typedef struct person {
	char name[20];  //����
	char tel[20];   //�绰
	char addr[50];  //סַ
}P;

//����һ���ṹ��ָ�룬���ڳ�ʼ��ʱ��̬����
P *people;

//��������ϵ�˵���ţ��ж���ϵ�˸����Ƿ񵽴������ֵ
int count=0;

//��������������ʼֵΪ20���ڳ����ʼ��ʱ����Ϊ count+20
int total=20;

//��������
void menu();                        //�����˵�
void add();                         //�����ϵ��
void del();                         //ɾ����ϵ��
void find();                        //������ϵ��
void edit();                        //�༭��ϵ��
void print();                       //�鿴ͨѶ¼
void output();                      //����ͨѶ¼
void output_txt();                  //����Ϊ�ı���ʽ
void output_csv();                  //����Ϊcsv��ʽ
void readfile();                    //��ȡ��ʷ����
void writefile();                   //�������
void my_retturn();                  //�˳�����
void printInfo(int i);              //��ӡ��ϵ����ϸ��Ϣ
int my_strcmp(char name[],int i);   //�Ƚ���������ͬ����1����ͬ����0
//������
int main()
{
    readfile();                         //��ȡ�ļ�����ʼ��
    int n;
    while (1) {
		menu();                         //�˵�
		scanf("%d", &n);
		switch (n) {
		case 1:add(); break;	        //�����ϵ��
		case 2:del(); break;	        //ɾ����ϵ��
		case 3:find(); break;	        //������ϵ��
		case 4:edit(); break;	        //�༭��ϵ��
		case 5:print(); break;	        //�鿴ͨѶ¼
		case 6:output(); break;        //����ͨѶ¼
		case 7:my_retturn();return 0;  //�˳�ϵͳ
		default:printf("�������ݲ��Ϸ������������룺\n");break;
        }
    }
	return 0;
}
//�˵�
void menu()
{
    printf("================================\n");
	printf("\tͨѶ¼����ϵͳ\n");
	printf("\t 1.�����ϵ��\n");
	printf("\t 2.ɾ����ϵ��\n");
	printf("\t 3.������ϵ��\n");
	printf("\t 4.�޸���ϵ��\n");
	printf("\t 5.�鿴ͨѶ¼\n");
	printf("\t 6.����ͨѶ¼\n");
	printf("\t 7.�˳�ͨѶ¼\n");
	printf("================================\n");
	printf("��ѡ��");
}
//�ж��ַ����Ƿ���ȣ����ڲ�ѯ��ɾ�����༭�Ȳ���
int my_strcmp(char name[],int i) {	//���������������ýṹ�������±�
	char* p1 = name;				//strcmp������ָ�룬���Խ�������ָ���ʾ
	char* p2 = (char*)&people[i].name;
	if (strcmp(p1, p2) == 0) {
		return 0;
	}
	return 1;
}
//��ӡ�����˵���Ϣ������ɾ���ͱ༭����
void printInfo(int i) {
	printf("���\t����\t\t�绰\t\t��ַ\n");
	printf("%2d\t%-5s\t\t%-16s%-50s\n", (i+1),people[i].name, people[i].tel,people[i].addr);
}
//1.�����ϵ��
void add()
{
    char chose;								    //�����ж��Ƿ�Ҫ�������
	while (1) {
        count++;								//���һ����ϵ�˾ͼ�һ
		if(count>=total)                        //�ж��Ƿ���Ҫ����
		{
		    total=total+20;
		    P *temp=NULL;
		    temp=realloc(people,total*sizeof(P));
		    if(temp==NULL)                      //����ʧ�ܣ����س�ʼ״̬
            {
                printf("�ڴ治�㣬�볢������Ӧ�ã�\n");
                count--;
                return;
            }
            free(people);                       //���ݳɹ����ͷ�ԭ�����ڴ�
            people=temp;
		}
		printf("��������ϵ�˵�������\n");
		scanf("%s", &people[count-1].name);
		getchar();
		printf("��������ϵ�˵ĵ绰��\n");
		scanf("%s", &people[count-1].tel);
		getchar();							       //���������
		while(strlen(people[count-1].tel)!=11)     //������11λ
        {
            printf("�������ݲ��Ϸ������������룺\n");
            scanf("%s", &people[count-1].tel);
            getchar();							   //���������
        }
		printf("��������ϵ�˵�סַ��\n");
		scanf("%s", &people[count-1].addr);
		getchar();
		printf("��ӳɹ����Ƿ������� Y/N��\n");
		scanf("%c", &chose);
		if (chose == 'y' || chose == 'Y') {	       //ѡ��y��Y�ͼ�����ӣ�����ֵ�˳�
			continue;						       //��������ѭ�����ص��ж�������
		}
		return;
	}
}
//2.ɾ����ϵ��
void del()
{
    if (count == 0) {						//�жϵ�ǰ�Ƿ�����ϵ��
		printf("��ǰû����ϵ�ˣ�\n");
		return;
	}
	char name[20];							//�������������Ҫɾ������ϵ������
	int chose=0;							//�����ж�
	printf("������Ҫɾ������ϵ��������\n");	//ɾ��������
	scanf("%s", name);
	int i;
	for (i = 0; i < count; i++) {
		if (my_strcmp(name,i) == 0) {		//���������������������ͬ��Ԫ��
			printf("ȷ��ɾ��������Ϣ��\n");	//��ʾ��ǰ��ϵ����Ϣ
			printInfo(i);					//��ʾ��ǰ����ϵ����Ϣ
			printf("1.ȷ�� 2.��һ��\n");		//��ʾ�Ƿ�ȷ��ɾ��
			scanf("%d", &chose);
			if (chose == 1) {
					for (i; i < count; i++) //����ɾ������
                        {
                            people[i] = people[i + 1];
                        }
				printf("ɾ���ɹ���\n");
				count--;					//��ϵ�˵ĸ���Ҫ��һ
				return;
			}
		}
	}
    printf("��ѯ������û���ҵ�����ϵ�ˣ�\n");	//û���ҵ�Ŀ�꣬��ʾû�д���
	return;
}
//3.������ϵ��
void find()
{
    int n=0;
    int i;
    if (count == 0) {						//�жϵ�ǰ�Ƿ�����ϵ��
		printf("��ǰû����ϵ�ˣ�\n");
		return;
	}
	printf("������Ҫ���ҵ���ϵ��������\n");	//��ʾ�����������
	char name[20];							//��������
	scanf("%s", name);
	printf("��ѯ�����\n");			        //��ʾ��ѯ���
	printf("���\t����\t\t�绰\t\t��ַ\n");
	for (i = 0; i < count; i++) {
		if (my_strcmp(name,i) == 0) {		//����������������ͬ��Ԫ��
            printf("%2d\t%-5s\t\t%-16s%-50s\n", (i+1),people[i].name, people[i].tel,people[i].addr);
			n++;
		}
	}
	if(n==0){
        printf("��ѯʧ�ܣ���ϵ�˲����ڣ�\n");			    //��ʾû���ҵ���ϵ��
	}
}
//4.�޸���ϵ��
void edit()
{
    if (count == 0) {					        //�жϵ�ǰ�Ƿ�����ϵ��
		printf("��ǰû����ϵ�ˣ�\n");
		return;
	}
	printf("������Ҫ�޸ĵ���ϵ��������\n");	    //����༭����
	char name[20];							    //��������
	int chose;								    //����ѡ��
	scanf("%s", name);
	getchar();
	int i;              						//���������
	for (i = 0; i < count; i++) {
		if (my_strcmp(name, i) == 0) {		    //����������������ͬ��Ԫ��
			printf("��ǰ��ϵ����ϢΪ��\n");	    //��ʾ�ҵ�����
			printInfo(i);					    //���������Ϣ
			printf("�Ƿ�ȷ���޸�?\n");          //��ʾ�Ƿ�ȷ�ϱ༭
			printf("1:ȷ�� 2����һ��\n");
			scanf("%d", &chose);			    //����ѡ��
			getchar();
			if (chose == 1) {
				printf("�������µ�������\n");   //��ʾ����������
				scanf("%s", &people[i].name);	//����������
				printf("�������µĵ绰��\n");	//��ʾ�����µ绰
				scanf("%s", &people[i].tel);	//�����µ绰
				printf("�������µĵ�ַ��\n");	//��ʾ�����µ�ַ
				scanf("%s", &people[i].addr);	//�����µ�ַ
				printf("�޸ĳɹ�����ǰ��ϵ����ϢΪ��\n");
				printInfo(i);					//��ʾ����ϵ����Ϣ
				return;
			}
		}
	}
	printf("��ѯ������û�и���ϵ�ˣ�\n");					//��ʾû�д���
}
//5.�鿴ͨѶ¼
void print()
{
    if (count == 0) {							//�жϵ�ǰ�Ƿ�����ϵ��
		printf("��ǰû����ϵ�ˣ�\n");
		return;
	}
	int i = 0;								    //�������±꣬�ӵ�һ��Ԫ�ؿ�ʼ���
	printf("���\t����\t\t�绰\t\tסַ\n");
	printf("----\t----\t\t----\t\t----\n");
	for (i = 0; i < count; i++) {
		printf("%2d\t%-5s\t\t%-16s%-50s\n", (i + 1), people[i].name, people[i].tel,people[i].addr);
	}
}
//6.����ͨѶ¼
void output(){
    int choose=0;
    printf("��ѡ�񵼳��ļ���ʽ��\n");
    printf("1:����Ϊ:ͨѶ¼.txt\n");
    printf("2:����Ϊ:ͨѶ¼.csv\n");
    printf("3:�˳�\n");
    while(1){
            scanf("%d",&choose);
        if (choose==1)        //����Ϊtxt�ļ�
        {
            output_txt();
            return;
        }
        else if(choose==2)   //����Ϊcsv�ļ�
        {
            output_csv();
            return;
        }
        else if(choose==3)  //�˳�
        {
            return;
        }
        else
        {
            printf("����������������룡\n");
        }
    }
}
//����Ϊ.txt�ļ�
void output_txt()
{
    FILE *fp;
    int i,j;
    if((fp = fopen("ͨѶ¼.txt","w")) == NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        printf("����ͨѶ¼ʧ�ܣ�\n");
        return;
    }
    fprintf(fp,"���\t����\t\t�绰\t\t      סַ\n");
    for(i=0;i<count;i++)
        {
            fprintf(fp,"%2d\t%-10s\t%-16s%-50s\n",i+1,people[i].name,people[i].tel,people[i].addr);
        }
    fclose(fp);
    printf("����ͨѶ¼�ɹ���\n");
}
//����Ϊ.csv�ļ�
void output_csv()
{
    FILE *fp;
    int i,j;
    if((fp = fopen("ͨѶ¼.csv","w")) == NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        printf("����ͨѶ¼ʧ�ܣ�\n");
        return;
    }
    fprintf(fp,"����,�绰,סַ\n");
    for(i=0;i<count;i++)
        {
            fprintf(fp,"%s,%s,%s\n",people[i].name,people[i].tel,people[i].addr);
        }
    fclose(fp);
    printf("����ͨѶ¼�ɹ���\n");
}
//7.�˳�ͨѶ¼
void my_retturn()
{
    writefile();    //�����ļ�
    free(people);   //�ͷ��ڴ�
    printf("===========ллʹ��!============\n");
}
//��ȡ�ļ�
void readfile()
{
    FILE *fp;
    int i=0;
    int flag=0;
    if((fp = fopen("data.bin","rb")) == NULL)
    {
        printf("===========��ӭʹ��!============\n");
        //��ʼ������
        people=(P *)malloc(total*sizeof(P));
        return;
    }
    //��ȡ��ǰͨѶ¼����
    fread(&count,sizeof(int),1,fp);         //�����ȡ
    total=count+20;
    //��ʼ������
    people=(P *)malloc(total*sizeof(P));
    //��ȡͨѶ¼��Ϣ
    while(!feof(fp))
    {
        if(people==NULL)
        {
            printf("��ʼ��ʧ�ܣ�\n");
            return;
        }
        fread(&people[i],sizeof(P),1,fp);   //�����ȡ
        i++;
    }
    fclose(fp);
}
//д�ļ�
void writefile()
{
    FILE *fp;
    if((fp = fopen("data.bin","wb")) == NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        printf("����ͨѶ¼ʧ�ܣ�\n");
        return;
    }
    fwrite(&count,sizeof(int),1,fp);        //����д��
    fwrite(people,sizeof(P),count,fp);      //����д��
    fclose(fp);
    return;
}
