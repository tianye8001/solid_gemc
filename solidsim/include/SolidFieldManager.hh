#ifndef SolidFieldManager_hh
#define SolidFieldManager_hh

#include <vector>

class SolidFieldMap;

/** SolidFieldManager

  This class reads in some input file that
  specifies the fields, and can then
  add them in the detector construction

  Requires a messenger class to know what the input
  file name is (to be implemented)

  Seamus Riordan
  Dec 3, 2010
  */

class SolidFieldManager {
    public:
	SolidFieldManager();
	~SolidFieldManager();

	void AddField(SolidFieldMap *m){ fFieldMaps.push_back(m);}
	int ProcessFieldMaps();
	const char *GetClassName(){ return "SolidFieldManager";}

	static SolidFieldManager *GetInstance();

    private:
	std::vector <SolidFieldMap *> fFieldMaps;

	static int __SolidFieldManagerInit;
	static SolidFieldManager *__SolidFieldManagerPtr;
};

#endif//SolidFieldManager_hh
