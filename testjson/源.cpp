
/* ����jsoncpp��ʹ��
* dxh1688@gmail.com
*/

#include <iostream>
#include "json/json.h"

using namespace std;
using namespace Json;    //json�������ռ�


void testarray();
int main()
{
	//string test = "{\"test\" : 5}";        //�������ĵ�json���͵�����
	//              
	////�����漰json�Ĳ��������ں������漰���˴�Ϊ��Ӧ�ã������ͣ��㶮��
	//Reader reader;
	//Value value;

	//if (reader.parse(test, value))
	//{
	//    int i = 0;

	//    if (!value["test"].isNull())
	//    {
	//        i = value["test"].asInt();
	//        cout << i << endl;
	//    }
	//}

	testarray();

	system("pause");

	return 0;
}


void testarray(){
	string strValue = "{\"ldh\":\"001\",\"gfc\":\"002\",\"yyj\":\"003\",\"andy\":[\"005\",\"123\",\"true\"]}";
	Json::Reader read;
	Json::Value value;
	value["t"] = "win_system_log";
	//value["lon_array"] = "002";

	for(int i=0;i<3;i++){
		Value value_ob;
		value_ob["�¼�"] = "6011";
		value_ob["����"] = "��Ϣ";
		value_ob["ʱ��"] = "2015-11-26 19:37:19";
		value_ob["��Դ"] = "EventLog";
		value_ob["�����"] = "37L4247F27-25";
		value_ob["[����]"] = "37L4247F27-25 WIN-JKKF8OI85IM";
		value["system_log_array"].append (value_ob);
	}
	//if( read.parse( strValue,value ) )
	/*{
		Json::Value val_array = value["andy"];
		int iSize = val_array.size();
		for ( int nIndex = 0;nIndex < iSize;++ nIndex )
		{
			cout<<val_array[nIndex]<<endl;
		}
	}*/

	cout<<value.toStyledString()<<"\n";

}


