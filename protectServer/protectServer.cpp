#include "baselib.h"
#include <stdio.h>

class protectServer
	:public BaseLib::ISingleton<protectServer>
	,public BaseLib::CTask
{
public:
	protectServer() {}
	~protectServer() {}
	INT32 Svc(void) {
		BaseLib::OS::sleep(1);
#ifdef _MACRO_OS_LINUX
		std::string strCmd("ps -eo comm|grep robotServerExe");
		std::string strRt = CmdResult(strCmd);
		if (strRt.find("robotServerExe")!=strRt.npos) {
			//std::cout << strRt << std::endl;			
		}
		else {
			list<string> lstDirs;
			GetUserDirs(lstDirs);
			lstDirs.push_back("");

			auto iter = lstDirs.begin();
			for (; iter != lstDirs.end();iter++) {
				//std::string strPath("/home/hr/robotSoft/robotServer/robotServerExe  8080");
				std::string strPath("/home/");
				strPath += iter->c_str();
				strPath += "/robotSoft/robotServer/robotServerExe";
				cout << strPath << endl;
				if (!BaseLib::IsFileExist(strPath.c_str())) {
					DBGPRINT(DBG_ERROR, "file is not exist :" << strPath);
				}
				BaseLib::CCreateProcess newProcess;
				newProcess.CreateNewProcess("pkill robotTeachHR");
				BaseLib::OS::sleep(1);
				strPath += " 8080";
				BOOL rt = newProcess.CreateNewProcess(strPath.c_str());
				DBGPRINT(DBG_ERROR, rt << "start:" << strPath);
				break;
			}
			
			//std::cout << "start:" << strPath << std::endl;
		}

#endif
		return TASK_CONTINUE;
	}
private:
#ifdef _MACRO_OS_LINUX
	std::string CmdResult(std::string strCmd)
	{
		std::string strRt("");

		FILE* fp;
		char sLine[1024];
		strCmd += " 2>&1";
		fp = popen(strCmd.c_str(), "r");
		if (NULL == fp)
		{
			DBGPRINT(DBG_ERROR, "popen error errno:" << errno << " " << strerror(errno));
			return "popen_error";
		}

		while (NULL != fgets(sLine, sizeof(sLine), fp))
		{
			strRt += sLine;
			memset(sLine, 0, 1024);
		}
		pclose(fp);

		return strRt;
	}
	BOOL GetUserDirs(list<string>& lstDirs) {
		std::stringstream o_Cmd, o_Rt;
		std::list<string> dir_list;
		BaseLib::CxxDirectoryList("/run/user", dir_list);
		list<string>::iterator iter = dir_list.begin();
		for (; iter != dir_list.end();iter++) {
			int uid = atoi((*iter).c_str());
			if (uid < 1000)
			{
				continue;
			}
			o_Cmd.str("");
			o_Cmd.clear();
			o_Cmd << "id -un " << uid << endl;
			string uName = CmdResult(o_Cmd.str());

			BaseLib::StringReplaceAll(uName, "\n", "");
			BaseLib::StringReplaceAll(uName, "\r", "");
			lstDirs.push_back(uName);
		}
	}
#endif // _MACRO_OS_LINUX
};
int main() {
	BaseLib::InitBaseLib();
	INIT_DBG_CODE;
	protectServer* protect = new protectServer();
	protect->Open();
	while (true)
	{
		BaseLib::OS::sleep(1);
	}
	std::cout << "return" << std::endl;
	protect->Close();
	return 0;
}