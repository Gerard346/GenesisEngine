#ifndef _FADE_H_
#define _FADE_H_

#include "Module.h"
#include "Globals.h"

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )

enum class fade_step {
	NONE,
	FADE_TO_BLACK,
	FADE_FROM_BLACK
};

class ModuleFade : public Module
{
public:
	ModuleFade(bool start_enabled = true);
	~ModuleFade();

	bool Init();
	bool CleanUp();

	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;

	bool FadeToBlack(float time);
	bool FadeToColor(float time);

	bool DrawFade();

	bool IsFading() const { return isFading; }
	fade_step GetFadeStep();
private:
	UINT32 start_time = NULL;
	UINT32 total_time = NULL;

	fade_step current_step = fade_step::NONE;

	bool isFading = false;
};
#endif