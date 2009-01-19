// Profile.h

#include "../../interface/HeeksObj.h"
#include "HeeksCNCTypes.h"

class CProfile;

class CProfileParams{
public:
	double m_tool_diameter;
	double m_clearance_height;
	double m_final_depth;
	double m_rapid_down_to_height;
	double m_horizontal_feed_rate;
	double m_vertical_feed_rate;
	double m_spindle_speed;
	int m_tool_on_side; // -1=right, 0=on, 1=left
	bool m_auto_roll_on;
	bool m_auto_roll_off;
	double m_roll_on_point[3];
	double m_roll_off_point[3];

	void set_initial_values();
	void write_values_to_config();
	void GetProperties(CProfile* parent, std::list<Property *> *list);
	void WriteXMLAttributes(TiXmlElement* pElem);
	void ReadFromXMLElement(TiXmlElement* pElem);
	void GetRollOnPos(HeeksObj* sketch, double &x, double &y);
	void GetRollOffPos(HeeksObj* sketch, double &x, double &y);
};

class CProfile: public HeeksObj{
public:
	std::list<int> m_sketches;
	CProfileParams m_params;

	CProfile(){}
	CProfile(const std::list<int> &sketches):m_sketches(sketches){m_params.set_initial_values();}

	// HeeksObj's virtual functions
	int GetType()const{return ProfileType;}
	const wxChar* GetTypeString(void)const{return _T("Profile");}
	void glCommands(bool select, bool marked, bool no_color);
	wxString GetIcon(){return _T("../HeeksCNC/icons/profile");}
	void GetProperties(std::list<Property *> *list);
	HeeksObj *MakeACopy(void)const;
	void CopyFrom(const HeeksObj* object);
	void WriteXML(TiXmlElement *root);
	bool CanAddTo(HeeksObj* owner);

	//int DoDialog();
	void AppendTextToProgram();

	static HeeksObj* ReadFromXMLElement(TiXmlElement* pElem);
};
