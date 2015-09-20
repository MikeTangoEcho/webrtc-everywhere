#include <string>
#include <memory>
#include <vector>

// http://www.w3.org/TR/mediacapture-streams/#idl-def-SourceInfo
typedef struct __SourceInfo {
	std::string sourceId;
	std::string kind;
	std::string label;
	std::string facing; // VideoFacingModeEnum 

	__SourceInfo(std::string _sourceId = "", std::string _kind = "", std::string _label = "") {
		sourceId = _sourceId;
		kind = _kind;
		label = _label;
	}
}
_SourceInfo;

template <typename T>
struct _Sequence {
	std::vector<std::shared_ptr<T> > values;
	_Sequence() {

	}
	void Clear() {
		values.clear();
	}
	void Add(std::shared_ptr<T> v) {
		values.push_back(v);
	}
	~_Sequence() {
		Clear();
	}
};
