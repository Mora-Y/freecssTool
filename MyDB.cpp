#include "MyDB.h"
using namespace std;

MyDB::MyDB(){
	connection = mysql_init(NULL); // ��ʼ�����ݿ����ӱ���
	if(connection == NULL){
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
}

MyDB::~MyDB(){
	if(connection != NULL) { // �ر����ݿ�����
		mysql_close(connection);
	}
}

bool MyDB::initDB(string host, string user, string pwd, string db_name)
{
	// ����mysql_real_connect����һ�����ݿ�����
	// �ɹ�����MYSQL*���Ӿ����ʧ�ܷ���NULL
	connection = mysql_real_connect(connection, host.c_str(),
			user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
	mysql_set_character_set(connection, "utf-8");
	if(connection == NULL) {
		cout << "Error:" << mysql_error(connection);
		return false;
	}
	return true;
}

bool MyDB::exeSQL(string sql, vector<string> &res){
	// mysql_query()ִ�гɹ�����0��ʧ�ܷ��ط�0ֵ����PHP�в�һ��
	if(mysql_query(connection, sql.c_str())) {
		return false;
	} else {
		result = mysql_store_result(connection); // ��ȡ�����
		if (result == NULL) return true;
		res.clear();
		// mysql_field_count()����connection��ѯ������
		int fieldcount = mysql_num_fields(result);
		while (row = mysql_fetch_row(result)){
			// mysql_num_fields()���ؽ�����е��ֶ���
			for(int j=0; j < fieldcount; ++j) {
				if (row[j] != NULL) {
					res.push_back(row[j]);
				} else {
					res.push_back("NULL");
				}
			}
		}
		mysql_free_result(result);
	}
	return true;
}

