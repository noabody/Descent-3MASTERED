#ifndef __SDLCONTROLLER_H_
#define __SDLCONTROLLER_H_

#include "Controller.h"
#include "joystick.h"

#define NULL_SDLCONTROLLER ((sbyte)NULL_CONTROLLER)

class gameSDLController : public gameController
{
public:
	gameSDLController(int num_funcs, ct_function *funcs, char *remote_adr = NULL);
	virtual ~gameSDLController();

	virtual void suspend();
	virtual void resume();
	virtual void poll(bool force = false);
	virtual void flush();

	virtual ct_config_data get_controller_value(ct_type type_req);
	virtual void set_controller_function(int id, const ct_type *type, ct_config_data value, const ubyte *flags);
	virtual void get_controller_function(int id, ct_type *type, ct_config_data *value, ubyte *flags);
	virtual void enable_function(int id, bool enable);
	virtual bool get_packet(int id, ct_packet *packet, ct_format alt_format = ctNoFormat);

	virtual float get_axis_sensitivity(ct_type axis_type, ubyte axis);
	virtual void set_axis_sensitivity(ct_type axis_type, ubyte axis, float val);
	virtual int assign_function(ct_function *fn);
	virtual void mask_controllers(bool joystick, bool mouse);

	virtual int get_mouse_raw_values(int *x, int *y);
	virtual unsigned get_joy_raw_values(int *x, int *y);
	virtual const char *get_binding_text(ct_type type, ubyte ctrl, ubyte bind);

	virtual void commit_axis_state() override;
	void set_controller_deadzone(int ctl, float deadzone);

private:
	int m_NumControls;
	int m_Suspended;
	bool m_JoyActive, m_MouseActive;

	struct t_controller {
		int id;
		ushort flags;
		ushort buttons;
		unsigned btnmask;
		float normalizer[CT_NUM_AXES];
		float sens[CT_NUM_AXES];
		float sensmod[CT_NUM_AXES];
		float deadzone;
		float commit_state[CT_NUM_AXES];
	} m_ControlList[CT_MAX_CONTROLLERS];

	struct ct_element {
		ct_format format;
		sbyte ctl[CTLBINDS_PER_FUNC];
		ubyte value[CTLBINDS_PER_FUNC];
		ct_type	ctype[CTLBINDS_PER_FUNC];
		ubyte flags[2];
		bool enabled;
	} m_ElementList[CT_MAX_ELEMENTS];

	struct ct_axis_button_state {
		float timer;
		float position;
		ubyte state;
	} m_AxisButtonStates[CT_MAX_ELEMENTS][CTLBINDS_PER_FUNC];

	bool enum_controllers(char *remote_adr);
	void assign_element(int id, ct_element *elem);

	sbyte get_axis_controller(ubyte axis);
	sbyte get_button_controller(ubyte btn);
	sbyte get_pov_controller(ubyte pov);

	float get_axis_value(sbyte controller, ubyte axis, ct_format format, bool invert = false);
	float get_raw_axis_value(sbyte controller, ubyte axis);
	float get_axis_button_value(int id, int slot, sbyte controller, ubyte axis, ct_format format);
	float get_button_value(sbyte controller, ct_format format, ubyte button);
	float get_pov_value(sbyte controller, ct_format format, ubyte pov_number, ubyte pov);
	float get_key_value(int key, ct_format format);

	void parse_ctl_file(int devnum, const char *ctlname);

private:
	struct t_msestate {
		int m_absX, m_absY;
		int m_deltaX, m_deltaY, m_deltaZ;
		unsigned int m_buttonMask;
	} m_MseState;

	struct t_extctlstate {
		int x, y, z, r, u, v;
		int pov[JOYPOV_NUM];
		int last_pov[JOYPOV_NUM];
		float povstarts[JOYPOV_NUM][JOYPOV_DIR];
		float povtimes[JOYPOV_NUM][JOYPOV_DIR];
		ubyte povpresses[JOYPOV_NUM][JOYPOV_DIR];
		unsigned buttons;
		ubyte btnpresses[CT_MAX_BUTTONS];
		float btnstarts[CT_MAX_BUTTONS];
		float btntimes[CT_MAX_BUTTONS];
	} m_ExtCtlStates[CT_MAX_EXTCTLS];

	float m_frame_timer_ms;
	float m_frame_timer;
	float m_frame_time;

	float m_mouse_rate_pending[2];
	float m_mouse_rate_cache[2];
	bool m_mouse_rate_cached[2];

	void extctl_getpos(int id);
	void extctl_geteval(int id);
	void mouse_geteval();
};

#endif
