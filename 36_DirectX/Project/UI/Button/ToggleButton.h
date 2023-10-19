#pragma once
class ToggleButton : public Button
{
public:
	
	ToggleButton(const string& toggleGroupKey, const Vector4& UDLR, const wstring& downFile, const byte& customKey = VK_LBUTTON, const wstring& upFile = L"", const wstring& hoverFile = L"");

	~ToggleButton();

	virtual void Update() override;
	virtual void Render() override;

private:

	// key & each toggle groups
	static map<string, vector<ToggleButton*>> toggleGroups;

	string myToggleKey{};

	byte customKey{VK_LBUTTON};
};

