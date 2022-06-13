#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//定义联系人结构体
typedef struct person {
	char name[20];  //姓名
	char tel[20];   //电话
	char addr[50];  //住址
}P;

//定义一个结构体指针，用于初始化时动态扩容
P *people;

//用于作联系人的序号，判断联系人个数是否到达了最大值
int count=0;

//定义总容量。初始值为20，在程序初始化时增加为 count+20
int total=20;

//函数声明
void menu();                        //导航菜单
void add();                         //添加联系人
void del();                         //删除联系人
void find();                        //查找联系人
void edit();                        //编辑联系人
void print();                       //查看通讯录
void output();                      //导出通讯录
void output_txt();                  //导出为文本格式
void output_csv();                  //导出为csv格式
void readfile();                    //读取历史数据
void writefile();                   //存放数据
void my_retturn();                  //退出程序
void printInfo(int i);              //打印联系人详细信息
int my_strcmp(char name[],int i);   //比较姓名，相同返回1，不同返回0
//主函数
int main()
{
    readfile();                         //读取文件，初始化
    int n;
    while (1) {
		menu();                         //菜单
		scanf("%d", &n);
		switch (n) {
		case 1:add(); break;	        //添加联系人
		case 2:del(); break;	        //删除联系人
		case 3:find(); break;	        //查找联系人
		case 4:edit(); break;	        //编辑联系人
		case 5:print(); break;	        //查看通讯录
		case 6:output(); break;        //导出通讯录
		case 7:my_retturn();return 0;  //退出系统
		default:printf("输入数据不合法，请重新输入：\n");break;
        }
    }
	return 0;
}
//菜单
void menu()
{
    printf("================================\n");
	printf("\t通讯录管理系统\n");
	printf("\t 1.添加联系人\n");
	printf("\t 2.删除联系人\n");
	printf("\t 3.查找联系人\n");
	printf("\t 4.修改联系人\n");
	printf("\t 5.查看通讯录\n");
	printf("\t 6.导出通讯录\n");
	printf("\t 7.退出通讯录\n");
	printf("================================\n");
	printf("请选择：");
}
//判断字符串是否相等，用于查询、删除、编辑等操作
int my_strcmp(char name[],int i) {	//接收输入的名字与该结构体数组下标
	char* p1 = name;				//strcmp参数是指针，所以将他们用指针表示
	char* p2 = (char*)&people[i].name;
	if (strcmp(p1, p2) == 0) {
		return 0;
	}
	return 1;
}
//打印单个人的信息，用于删除和编辑操作
void printInfo(int i) {
	printf("序号\t姓名\t\t电话\t\t地址\n");
	printf("%2d\t%-5s\t\t%-16s%-50s\n", (i+1),people[i].name, people[i].tel,people[i].addr);
}
//1.添加联系人
void add()
{
    char chose;								    //用于判断是否要继续添加
	while (1) {
        count++;								//添加一个联系人就加一
		if(count>=total)                        //判断是否需要扩容
		{
		    total=total+20;
		    P *temp=NULL;
		    temp=realloc(people,total*sizeof(P));
		    if(temp==NULL)                      //扩容失败，返回初始状态
            {
                printf("内存不足，请尝试重启应用！\n");
                count--;
                return;
            }
            free(people);                       //扩容成功，释放原来的内存
            people=temp;
		}
		printf("请输入联系人的姓名：\n");
		scanf("%s", &people[count-1].name);
		getchar();
		printf("请输入联系人的电话：\n");
		scanf("%s", &people[count-1].tel);
		getchar();							       //清除缓冲区
		while(strlen(people[count-1].tel)!=11)     //必须是11位
        {
            printf("输入数据不合法，请重新输入：\n");
            scanf("%s", &people[count-1].tel);
            getchar();							   //清除缓冲区
        }
		printf("请输入联系人的住址：\n");
		scanf("%s", &people[count-1].addr);
		getchar();
		printf("添加成功！是否继续添加 Y/N：\n");
		scanf("%c", &chose);
		if (chose == 'y' || chose == 'Y') {	       //选择y或Y就继续添加，其他值退出
			continue;						       //结束本次循环，回到判断条件处
		}
		return;
	}
}
//2.删除联系人
void del()
{
    if (count == 0) {						//判断当前是否有联系人
		printf("当前没有联系人！\n");
		return;
	}
	char name[20];							//用来接收输入的要删除的联系人姓名
	int chose=0;							//用作判断
	printf("请输入要删除的联系人姓名：\n");	//删除的姓名
	scanf("%s", name);
	int i;
	for (i = 0; i < count; i++) {
		if (my_strcmp(name,i) == 0) {		//在数组里查找与输入名相同的元素
			printf("确认删除以下信息？\n");	//提示当前联系人信息
			printInfo(i);					//显示当前的联系人信息
			printf("1.确认 2.下一个\n");		//提示是否确认删除
			scanf("%d", &chose);
			if (chose == 1) {
					for (i; i < count; i++) //进行删除操作
                        {
                            people[i] = people[i + 1];
                        }
				printf("删除成功！\n");
				count--;					//联系人的个数要减一
				return;
			}
		}
	}
    printf("查询结束，没有找到该联系人！\n");	//没有找到目标，提示没有此人
	return;
}
//3.查找联系人
void find()
{
    int n=0;
    int i;
    if (count == 0) {						//判断当前是否有联系人
		printf("当前没有联系人！\n");
		return;
	}
	printf("请输入要查找的联系人姓名：\n");	//提示输入查找姓名
	char name[20];							//接收姓名
	scanf("%s", name);
	printf("查询结果：\n");			        //提示查询结果
	printf("序号\t姓名\t\t电话\t\t地址\n");
	for (i = 0; i < count; i++) {
		if (my_strcmp(name,i) == 0) {		//查找与输入姓名相同的元素
            printf("%2d\t%-5s\t\t%-16s%-50s\n", (i+1),people[i].name, people[i].tel,people[i].addr);
			n++;
		}
	}
	if(n==0){
        printf("查询失败，联系人不存在！\n");			    //提示没有找到联系人
	}
}
//4.修改联系人
void edit()
{
    if (count == 0) {					        //判断当前是否有联系人
		printf("当前没有联系人！\n");
		return;
	}
	printf("请输入要修改的联系人姓名：\n");	    //输入编辑姓名
	char name[20];							    //接收姓名
	int chose;								    //用于选择
	scanf("%s", name);
	getchar();
	int i;              						//清除缓存区
	for (i = 0; i < count; i++) {
		if (my_strcmp(name, i) == 0) {		    //查找与输入姓名相同的元素
			printf("当前联系人信息为：\n");	    //提示找到此人
			printInfo(i);					    //输入此人信息
			printf("是否确认修改?\n");          //提示是否确认编辑
			printf("1:确认 2：下一个\n");
			scanf("%d", &chose);			    //输入选择
			getchar();
			if (chose == 1) {
				printf("请输入新的姓名：\n");   //提示输入新姓名
				scanf("%s", &people[i].name);	//输入新姓名
				printf("请输入新的电话：\n");	//提示输入新电话
				scanf("%s", &people[i].tel);	//输入新电话
				printf("请输入新的地址：\n");	//提示输入新地址
				scanf("%s", &people[i].addr);	//输入新地址
				printf("修改成功！当前联系人信息为：\n");
				printInfo(i);					//显示新联系人信息
				return;
			}
		}
	}
	printf("查询结束，没有该联系人！\n");					//提示没有此人
}
//5.查看通讯录
void print()
{
    if (count == 0) {							//判断当前是否有联系人
		printf("当前没有联系人！\n");
		return;
	}
	int i = 0;								    //作数组下标，从第一个元素开始输出
	printf("序号\t姓名\t\t电话\t\t住址\n");
	printf("----\t----\t\t----\t\t----\n");
	for (i = 0; i < count; i++) {
		printf("%2d\t%-5s\t\t%-16s%-50s\n", (i + 1), people[i].name, people[i].tel,people[i].addr);
	}
}
//6.导出通讯录
void output(){
    int choose=0;
    printf("请选择导出文件格式：\n");
    printf("1:导出为:通讯录.txt\n");
    printf("2:导出为:通讯录.csv\n");
    printf("3:退出\n");
    while(1){
            scanf("%d",&choose);
        if (choose==1)        //导出为txt文件
        {
            output_txt();
            return;
        }
        else if(choose==2)   //导出为csv文件
        {
            output_csv();
            return;
        }
        else if(choose==3)  //退出
        {
            return;
        }
        else
        {
            printf("输入错误，请重新输入！\n");
        }
    }
}
//导出为.txt文件
void output_txt()
{
    FILE *fp;
    int i,j;
    if((fp = fopen("通讯录.txt","w")) == NULL)
    {
        printf("文件打开失败！\n");
        printf("导出通讯录失败！\n");
        return;
    }
    fprintf(fp,"序号\t姓名\t\t电话\t\t      住址\n");
    for(i=0;i<count;i++)
        {
            fprintf(fp,"%2d\t%-10s\t%-16s%-50s\n",i+1,people[i].name,people[i].tel,people[i].addr);
        }
    fclose(fp);
    printf("导出通讯录成功！\n");
}
//导出为.csv文件
void output_csv()
{
    FILE *fp;
    int i,j;
    if((fp = fopen("通讯录.csv","w")) == NULL)
    {
        printf("文件打开失败！\n");
        printf("导出通讯录失败！\n");
        return;
    }
    fprintf(fp,"姓名,电话,住址\n");
    for(i=0;i<count;i++)
        {
            fprintf(fp,"%s,%s,%s\n",people[i].name,people[i].tel,people[i].addr);
        }
    fclose(fp);
    printf("导出通讯录成功！\n");
}
//7.退出通讯录
void my_retturn()
{
    writefile();    //保存文件
    free(people);   //释放内存
    printf("===========谢谢使用!============\n");
}
//读取文件
void readfile()
{
    FILE *fp;
    int i=0;
    int flag=0;
    if((fp = fopen("data.bin","rb")) == NULL)
    {
        printf("===========欢迎使用!============\n");
        //初始化数组
        people=(P *)malloc(total*sizeof(P));
        return;
    }
    //读取当前通讯录总数
    fread(&count,sizeof(int),1,fp);         //按块读取
    total=count+20;
    //初始化数组
    people=(P *)malloc(total*sizeof(P));
    //读取通讯录信息
    while(!feof(fp))
    {
        if(people==NULL)
        {
            printf("初始化失败！\n");
            return;
        }
        fread(&people[i],sizeof(P),1,fp);   //按块读取
        i++;
    }
    fclose(fp);
}
//写文件
void writefile()
{
    FILE *fp;
    if((fp = fopen("data.bin","wb")) == NULL)
    {
        printf("文件打开失败！\n");
        printf("导出通讯录失败！\n");
        return;
    }
    fwrite(&count,sizeof(int),1,fp);        //按块写入
    fwrite(people,sizeof(P),count,fp);      //按块写入
    fclose(fp);
    return;
}
