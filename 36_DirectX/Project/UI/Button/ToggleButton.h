#pragma once

#define C_SELECT_FUNC_P function<void(const CharacterType& cType, const PlayerType& pType)>

class ToggleButton : public Button
{
public:
	
	ToggleButton(const string& toggleGroupKey, const Vector4& UDLR, const wstring& downFile, const byte& customKey = VK_LBUTTON, const wstring& upFile = L"", const wstring& hoverFile = L"");

	~ToggleButton();

	virtual void Update() override;
	virtual void Render() override;

	void SetCSelectEvent(C_SELECT_FUNC_P Event) { this->CharacterSelectEvent = Event; }

private:

	// key & each toggle groups
	static map<string, vector<ToggleButton*>> toggleGroups;
	
	C_SELECT_FUNC_P CharacterSelectEvent = nullptr;

	string myToggleKey{};

	byte customKey{VK_LBUTTON};
};

