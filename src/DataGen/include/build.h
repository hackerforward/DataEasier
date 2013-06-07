


public class Build
{
private:
	vector< vector<string> > chwordVec;
	vector< vector<string> > enwordVec;
	set<string> uniqChword;
	set<string> uniqEnword;
	set<string> uniqPhoneNum;
	set<string> uniqDate;
	int seed;

public:
	Build();
	~Build();
	string gen_ChSentence(int id);
	string gen_EnSentence(int id);
	string gen_PhoneNum(int id);
	string gen_ShortDate(int id);
	string gen_LongDate(int id);
	string gen_Sequence(int id);
	string gen_IpAddress(int id);
}
