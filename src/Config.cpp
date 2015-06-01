#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <Python.h>

#include "Config.h" 
#include "Question.h"
#include "Main.h"

void Config::init(std::string filename) {
	Py_Initialize();

    FILE* set = fopen(filename.c_str(), "r");
	std::string tmpPath = Py_GetPath();
    tmpPath += ":";
	std::string tmp;

	// Yes, it is supposed to be removing the last part after '/'
	for (size_t i = 0; i < filename.size(); i++) {
		if (filename[i] == '/') {
			tmpPath += tmp + "/";
			tmp = "";
		} else {
			tmp.push_back(filename[i]);
		}
	}

    PySys_SetPath(&tmpPath[0]);
    PyRun_SimpleFile(set, filename.c_str());
    PyObject* mainModule = PyImport_AddModule("__main__");
    PyObject* mainDict = PyModule_GetDict(mainModule);
    PyObject* confDict = PyDict_GetItemString(mainDict, "conf");

    settings.colorStep = PyFloat_AsDouble(PyDict_GetItemString(confDict, "colorStep"));
    settings.fontName = PyString_AsString(PyDict_GetItemString(confDict, "font")); 

    PyObject* mainFunc = PyDict_GetItemString(mainDict, "main");
    PyObject* result = PyObject_CallObject(mainFunc, NULL);

    int listSize = PyList_Size(result);
    for (int i = 0; i < listSize; i++) {
        PyObject* cur = PyList_GetItem(result, i);
        questions.push_back(new Question(
            PyString_AsString(PyDict_GetItemString(cur, "question")),
            PyString_AsString(PyDict_GetItemString(cur, "answer")),
            [cur] (std::string a, std::string b) -> bool {
                PyObject* dict = PyObject_CallFunction (
                        PyDict_GetItemString(cur, "checker"),
                        "ss",
                        a.c_str(), b.c_str()
                );
                if (!dict || !PyDict_Check(dict)) exit(0);
				Main::getInstance()->msgFromChecker = PyString_AsString(PyDict_GetItemString(dict, "msg"));
                return PyObject_Compare(PyDict_GetItemString(dict, "result"), Py_True) == 0;
            }
        ));
    }

	// Commented for lambdas above to work with VM
    //Py_Finalize();
}
