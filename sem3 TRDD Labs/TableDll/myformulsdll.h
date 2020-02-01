#ifndef MYFORMULSDLL_H
#define MYFORMULSDLL_H

#include "myformulsdll_global.h"

class MYFORMULSDLLSHARED_EXPORT MyFormulsDll
{

public:
    MyFormulsDll();
    double work_for_ventilator(double, double, double, double, double);
    double temp_for_kvd(double, double, double, double);
    double press_for_kvd(double, double, double, double, double);
    double work_for_kvd(double, double, double, double, double);
    double work_for_tvd(double, double);
    double adiabatt_speed(double, double);
    double speed_turbine(double, double, double);
    double tvd_temperature(double, double, double, double);
    double temp_paddle(double, double, double, double);
    double temp_cold(double, double);
    double temp_paddle_cold(double, double, double);
    double high_tvd(double, double, double, double, double);
    double ratio(double, double, double, double, double);
    double all_press(double, double, double);
    double all_press_behind(double, double);
    double rate_tvd(double, double);
    double area_tvd(double, double, double, double, double, double, double, double);
    double high_paddle_step(double, double);
    double dia_tvd_m(double, double);
    double dia_tvd(double, double);
    double dia_tvd_last_m(double, double);
    double dia_tvd_last_step(double, double);
    double tvd_gas(double, double);
    double area_circle(double, double,double,double, double);
    double middle_dia_tvd();
    double outer_dia(double, double);
    double outer_dia2(double, double);
    double frequency_gas(double, double);
    double temp_kvd_out(double, double);
    double press_kvd(double, double);
    double kritic_speed(double, double, double);
    double kvd_speed2(double, double);
    double tvd_gas_output(double, double);
    double kvd_area_channel(double, double,double,double, double,double,double);
    double pokaz(double,double, double);
    double ratio_ring(double, double, double, double);
    double area_ring_kvd(double, double);
    double dia_kvd(double,double);
    double dia_kvd_in(double,double);
    double middle_dia_kvd(double, double);
    double high_kvd_1(double, double);
    double high_kvd_2(double, double);
    double high_kvd_3(double, double);
    double circle_speed_kvd(double, double);
    double middle_dia_for_kvd_1(double, double);
    double middle_dia_for_kvd_2(double);
    double middle_dia_for_kvd_3(double, double);
    double middle_dia_for_tvd2(double);
    double steps(double, double, double);
    double dia_knd_1(double, double, double, double, double,double, double,double, double);
    double knd_dia(double,double);
    double middle_dia_knd(double, double);
    double politrop_knd();
    double ratio_knd(double, double);
    double area_knd(double, double,double, double,double, double, double,double, double);
    double relative_knd1(double, double);
    double relative_knd2(double, double);
    double relative_knd3(double, double);
    double outer_dia_knd1();
    double outer_dia_knd2(double, double);
    double outer_dia_knd3(double, double);
    double dia_knd_out();
    double dia_knd_midd();
    double freak_ven(double, double);
    double f_vh(double, double,double,double,double, double,double);
    double f_vyh_2k(double, double);
    double kromka(double, double);
    double dia_tnd();
    double work_for_tnd(double, double, double);
    double temp_for_tnd(double, double, double, double);
    double ratio_tnd(double, double,double, double,double);
    double all_press_tnd();
    double rash_tnd(double, double);
    double area_tnd(double, double,double, double,double, double, double,double);
    double high_tnd(double, double);
    double middle_tnd(double, double);
    double area_tnd_circle(double,double,double,double,double);
    double mid_dia_tnd();
    double input_tnd(double, double);
    double output_tnd(double, double);
    double polusumma();
    double polusumma_knd(double, double);
    double steps_tnd(double ratio_knd_tnd, double Z_vent,double m,double polusumma, double polusumma_knd);
    double krug_speed(double mid_dia_tnd, double n_vent);
    double param_nag(double, double, double,double);
    double temp_padd_tnd(double, double, double, double);
    double volt(double, double,double,double);
    double zapas_steps(double, double);
    double temp_for_tnd2(double, double,double, double);
    double temp_paddl_tnd(double, double, double);
};

#endif // MYFORMULSDLL_H
