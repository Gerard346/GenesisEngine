#ifndef  _UI_H_
#define _UI_H_

#include "Module.h"
#include "Globals.h"

class UI : public Module {
public:
	UI(bool start_enabled = true);
	~UI();

	bool Init();
	bool CleanUp();

	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;

	void SetUpOrtho();
	void ResetRender();

private:

};

#endif // ! _UI_H_
