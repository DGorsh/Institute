#include "myformulsdll.h"
#include <math.h>

MyFormulsDll::MyFormulsDll()
{
}

double MyFormulsDll::work_for_ventilator(double adiabatt, double gas, double temp, double power_press_knd, double kpd_vent) {
    double work_knd;
    work_knd = ((adiabatt*gas*temp)/ (kpd_vent*(adiabatt - 1)))*((pow(power_press_knd, ((adiabatt - 1) / adiabatt))) - 1);
    return work_knd;
}

double MyFormulsDll::temp_for_kvd(double temp, double work_for_ventilator1, double adiabatt, double gas) {
    double temp_kvd;
    temp_kvd = temp + ((work_for_ventilator1) *(adiabatt - 1)/(adiabatt*gas));
    return temp_kvd;
}

double MyFormulsDll::press_for_kvd(double power_press_knd, double sett, double koeff_recovery, double koeff_save, double koeff_knd_kvd) {
    double pressure_kvd;
    pressure_kvd = power_press_knd*sett*((koeff_recovery*koeff_save) / koeff_knd_kvd);
    return pressure_kvd;
}
double MyFormulsDll::work_for_kvd(double adiabatt, double pressure, double temp_kvd, double power_kvd, double now) {
    double work_compress;
    work_compress = (adiabatt / (adiabatt - 1))*pressure*temp_kvd*(pow(power_kvd, ((adiabatt - 1) / adiabatt)) - 1) * 1 / now;
    return work_compress;

}

double MyFormulsDll::work_for_tvd(double work_for_kvd, double adiabatt) {
    double work_tur;
    work_tur = work_for_kvd / adiabatt;
    return work_tur;
}

double MyFormulsDll::adiabatt_speed(double work_for_tvd, double power_tvd) {
    double speed;
    speed = sqrt((2 * work_for_tvd) / power_tvd);
    return speed;
}

double MyFormulsDll::speed_turbine(double parsons, double adiabatt_speed1, double step_tvd) {
    double speed;
    speed = parsons*adiabatt_speed1*sqrt(1 / step_tvd);
    return speed;
}
double MyFormulsDll::tvd_temperature(double temperature, double work_for_tvd, double adiabatt, double gas) {
    double gas_temp;
    gas_temp = temperature - work_for_tvd*(adiabatt - 1) / (adiabatt*gas);
    return gas_temp;
}
double MyFormulsDll::temp_paddle(double tvd_temperature, double spped_turbine, double adiabatt, double gas_ker){
    double temp;
    temp = 0.95 * (tvd_temperature + (pow(spped_turbine,2)*(adiabatt - 1)) /( 2 * adiabatt*gas_ker));
    return temp;
}

double MyFormulsDll::temp_cold(double temp_for_kvd, double work_for_kvd) {
    double res;
    res = temp_for_kvd + work_for_kvd / 1005;
    return res;
}

double MyFormulsDll::temp_paddle_cold(double temp_paddle, double temp_freesize, double temp_cold) {
    double res;
    res = temp_paddle / 0.95 - temp_freesize*(temp_paddle / 0.95 - temp_cold);
    return res;
}

double MyFormulsDll::high_tvd(double speed_turbine, double sett, double koeff_paddle, double koeff_hard_paddle, double limit_paddle) {
    double res;
    res = (2 * pow(speed_turbine, 2)*sett*koeff_paddle*koeff_hard_paddle) / (limit_paddle * 1000000);
    return res;
}

double MyFormulsDll::ratio(double work_for_tvd, double adibatt, double press, double temp, double koeff) {
    double res;
    res = 1 / (pow(1 - work_for_tvd / (adibatt*press*temp*koeff / (adibatt - 1)), temp / (temp - 1)));
    return res;
}

double MyFormulsDll::all_press(double press_for_kvd, double power_kvd, double koeff_recovery) {
    double res;
    res = press_for_kvd*power_kvd*koeff_recovery;
    return res;
}

double MyFormulsDll::all_press_behind(double all_press2, double ratio1) {
    double res;
    res= all_press2/ratio1;
    return res;
}

double MyFormulsDll::rate_tvd(double adibat_g, double speed_step) {
    double res;
    res = pow((adibat_g + 1) / 2, (1 / (adibat_g - 1)))*pow(1 - (adibat_g - 1)*pow(speed_step, 2) / (adibat_g + 1), 1 / (adibat_g - 1))*speed_step;
    return res;
}

double MyFormulsDll::area_tvd(double rate_for_tvd, double rate_cold, double rate_for_kvd, double tvd_temperature, double koeff_ker, double all_press_behind, double speed_tvd, double angle)  {
    double res;
    res = ((rate_for_tvd + rate_cold*rate_for_kvd)*sqrt(tvd_temperature)) / (koeff_ker*all_press_behind*speed_tvd*sin(angle));
    return res;
}

double MyFormulsDll::high_paddle_step(double area_tvd, double high_tvd) {
    double res, x;
    x = 0.76 * high_tvd;
    res = (sqrt(area_tvd)/(sqrt(x)));
    return res;
}
double MyFormulsDll::dia_tvd_m(double high_paddle_step, double high_tvd) {
    double res;
    res = high_paddle_step*high_tvd;
    return res;
}

double MyFormulsDll::dia_tvd(double dia_tvd_m, double area_tvd) {
    double res, x;
    x = 0.63 * area_tvd;
    res = sqrt(pow(dia_tvd_m, 2) + x);
    return res;
}

double MyFormulsDll::dia_tvd_last_m(double dia_tvd_m, double area_tvd) {
    double res, x;
    x = 0.63 * pow(area_tvd, 2);
    res = sqrt(pow(dia_tvd_m, 2) - x);
    return res;
}

double MyFormulsDll::dia_tvd_last_step(double dia_tvd_last_m1, double dia_tvd1) {
    double res;
    res = dia_tvd_last_m1/dia_tvd1;
    return res;
}

double MyFormulsDll::tvd_gas(double  tvd_temperature1, double speed_for_tvd){
    double res;
    res=pow(((tvd_temperature1+1)/2), (1/(tvd_temperature1-1)))*pow((1-((tvd_temperature1-1)/(tvd_temperature1+1))*pow(speed_for_tvd, 2)), (1/(tvd_temperature1)))*speed_for_tvd;
    return res;
}

double MyFormulsDll::area_circle(double gas_tvd, double tvd_for_temp,double koeff_kerosin, double all_press1, double tvd_gas){
    double res;
    res=(gas_tvd*sqrt(tvd_for_temp))/(koeff_kerosin*all_press1*tvd_gas);
    return res;
}
double MyFormulsDll::middle_dia_tvd(){
    double res;
    res= 0.58;
    return res;
}
double MyFormulsDll::outer_dia(double middle_dia_tvd1, double area_tvd1){
    double res, x;
    x = 0.63 *area_tvd1;
    res = sqrt(pow( middle_dia_tvd1, 2) + x);
    return res;
}

double MyFormulsDll::outer_dia2(double middle_dia_tvd1, double area_tvd1){
    double res, x;
    x = 0.63 *area_tvd1;
    res = sqrt(pow( middle_dia_tvd1, 2) - x);
    return res;
}
double MyFormulsDll::frequency_gas(double speed_turbine1, double middle_dia_tvd1){
    double res;
    res=(60*speed_turbine1)/(3.14*middle_dia_tvd1);
    return res;
}
double MyFormulsDll::temp_kvd_out(double temp_for_kvd1, double work_for_kvd1){
    double res;
    res=temp_for_kvd1+work_for_kvd1/1005;
    return res;
}
double MyFormulsDll::press_kvd(double degree_kvd, double press_for_kvd1){
    double res;
    res=degree_kvd*press_for_kvd1;
    return res;
}
double MyFormulsDll::kritic_speed(double koeff_ad, double R, double temp_kvd_out1){
    double res;
    res= sqrt(2*(koeff_ad/(koeff_ad+1))*R*temp_kvd_out1);
    return res;
}
double MyFormulsDll::kvd_speed2(double lambada_output_kvd, double kritic_speed1){
    double res;
    res=lambada_output_kvd*kritic_speed1;
    return res;
}

double MyFormulsDll::tvd_gas_output(double  koeff_adiabatt, double lambada_output_kvd){
    double res;
    res=pow(((koeff_adiabatt+1)/2), (1/(koeff_adiabatt-1)))*pow((1-((koeff_adiabatt-1)/(koeff_adiabatt+1))*pow(lambada_output_kvd, 2)), (1/(koeff_adiabatt)))*lambada_output_kvd;
    return res;
}

double MyFormulsDll::kvd_area_channel(double G_v_kvd, double q_tvd,double temp_kvd_out1,double S_v, double press_kvd1,double tvd_gas_output1,double koeff_G){
    double res;
    res=((G_v_kvd-q_tvd*G_v_kvd)*sqrt(temp_kvd_out1))/(S_v*press_kvd1*tvd_gas_output1*koeff_G);
    return res;


}

double MyFormulsDll::pokaz(double Pi_kvd,double temp_kvd_out1, double temp_for_kvd1){
    double res, t;
    t=log10(Pi_kvd)/(log10(temp_kvd_out1/temp_for_kvd1));
    res=-t/(1-t);
    return res;
}

double MyFormulsDll::ratio_ring(double Pi_kvd, double pokaz1, double tvd_gas_output, double q_lam_kvd){
    double res;
    res=pow(Pi_kvd, ((pokaz1+1)/2*pokaz1))*(tvd_gas_output/q_lam_kvd);
    return res;
}
double MyFormulsDll::area_ring_kvd(double ratio_ring1, double kvd_area_channel1){
    double res;
    res= ratio_ring1*kvd_area_channel1;
    return res;
}

double MyFormulsDll::dia_kvd(double area_ring_kvd,double dia_kvd_output){
    double res;
    res=sqrt((4*area_ring_kvd)/(3.14*(1-dia_kvd_output)));
    return res;
}

double MyFormulsDll::dia_kvd_in(double dia_kvd_output,double dia_kvd1){
    double res;
    res= dia_kvd_output*dia_kvd1;
    return res;
}

double MyFormulsDll::middle_dia_kvd(double dia_kvd1, double dia_kvd_output){
    double res;
    res=dia_kvd1*sqrt((1+pow(dia_kvd_output, 2))/2);
    return res;
}

double MyFormulsDll::high_kvd_1(double dia_kvd_output, double dia_kvd_in1){
    double res;
    res=((1-dia_kvd_output)/2)*dia_kvd_in1;
    return res;
}
double MyFormulsDll::high_kvd_2(double kvd_area_channel1, double middle_dia_kvd1){
    double res;
    res=kvd_area_channel1/(3.14*middle_dia_kvd1);
    return res;
}

double MyFormulsDll::high_kvd_3(double dia_kvd_output, double dia_kvd1){
    double res;
    res=0.5*((1/dia_kvd_output) -1)*dia_kvd1;
    return res;
}

double MyFormulsDll::circle_speed_kvd(double dia_kvd1, double frequency_gas1){
    double res;
    res=(3.14*dia_kvd1*frequency_gas1)/60;
    return res;
}

double MyFormulsDll::middle_dia_for_kvd_1(double dia_kvd1, double hight_kvd_3){
    double res;
    res=dia_kvd1-hight_kvd_3;
    return res;
}

double MyFormulsDll::middle_dia_for_kvd_2(double middle_dia_kvd){
    double res;
    res=middle_dia_kvd;
    return res;
}

double MyFormulsDll::middle_dia_for_kvd_3(double dia_kvd_in, double hight_kvd_3){
    double res;
    res=dia_kvd_in+hight_kvd_3;
    return res;
}
double MyFormulsDll::middle_dia_for_tvd2(double dia_tvd_m){
    double res;
    res=dia_tvd_m;
    return res;
}

double MyFormulsDll::steps(double middle_dia_for_tvd2, double middle_dia_kvd, double k_gg){
    double res;
    res=pow((middle_dia_for_tvd2/middle_dia_kvd),2)*(1/k_gg);
    return res;
}
double MyFormulsDll::dia_knd_1(double G_v, double T, double S_v, double P, double di_knd,double q_knd, double koeff_G,
                               double q_input, double Q_bha){
 double x,res;
 x=3.14;
 res=2*sqrt((G_v*sqrt(T))/(x*S_v*P*(1-pow(di_knd,2))*q_knd*koeff_G*q_input*Q_bha));
 return res;
}

double MyFormulsDll::knd_dia(double dia_knd_1,double middle_dia_knd){
    double res;
    res=0.5*dia_knd_1+middle_dia_knd;
    return res;
}
double MyFormulsDll::middle_dia_knd(double dia_knd_1, double di_knd){
    double res;
    res=dia_knd_1*di_knd;
    return res;
}
double MyFormulsDll::politrop_knd(){//нигде не назадано T_вых КНД
    double res;
    res=1.51;
    return res;
}

double MyFormulsDll::ratio_knd(double Pi_v, double politrop_knd){
    double res;
    res=pow(Pi_v, ((politrop_knd+1)/(politrop_knd*2)));
    return res;
}

double MyFormulsDll::area_knd(double G_v, double T,double S_v, double P,double q_input,
                              double  Q_bha, double q_knd,double K_g_vent, double ratio_knd){
    double res;
    res=(G_v*sqrt(T))/(S_v*P*q_input*Q_bha*q_knd*K_g_vent*ratio_knd);
    return res;
}
double MyFormulsDll::relative_knd1(double dia_knd_1, double area_kvd){
    double res;
    res=(sqrt(pow(dia_knd_1,2)-(4*area_kvd/3.14)))/dia_knd_1;
    return res;
}

double MyFormulsDll::relative_knd2(double knd_dia, double area_kvd){
    double res;
    res=sqrt((3.14*pow(knd_dia,2)-area_kvd)/(2*area_kvd+3.14*pow(knd_dia,2)));
    return res;
}

double MyFormulsDll::relative_knd3(double middle_dia_knd, double area_kvd){
    double res;
    res=middle_dia_knd/(sqrt(pow(middle_dia_knd,2)+4*area_kvd/3.14));
    return res;
}

double MyFormulsDll::outer_dia_knd1(){
    double res;
    res=0.94;
    return res;
}

double MyFormulsDll::outer_dia_knd2(double area_knd, double knd_dia){
    double res;
    res=sqrt((2*area_knd)/3.14 + pow(knd_dia, 2));
    return res;
}

double MyFormulsDll::outer_dia_knd3(double middle_dia_knd, double relative_knd3){
    double res;
    res=middle_dia_knd/relative_knd3;
    return res;
}

double MyFormulsDll::dia_knd_out(){// какое значение из D_нарКНДвых брать?...
    double res;
    res=0.51;
    return res;
}

double MyFormulsDll::dia_knd_midd(){// какое значение из D_нарКНДвых брать?...
    double res;
    res=0.63;
    return res;
}

double MyFormulsDll::freak_ven(double U_1st, double dia_knd_1){
    double res;
    res=(60*U_1st)/(3.14*dia_knd_1);
    return res;
}

double MyFormulsDll::f_vh(double G_v_kvd, double temp_for_kvd,double S_v,double press_for_kvd,
                          double q_lam_kvd, double koeff_G,double alpha_v_vyh){
    double res;
    res=(G_v_kvd*sqrt(temp_for_kvd))/(S_v*press_for_kvd*q_lam_kvd*koeff_G*sin(alpha_v_vyh));
    return res;
}

double MyFormulsDll::f_vyh_2k(double area_knd, double f_vh){
    double res;
    res=area_knd-f_vh;
    return res;
}

double MyFormulsDll::kromka(double outer_knd1, double f_vyh_2k){
    double res;
    res=sqrt(pow(outer_knd1,2)-4*f_vyh_2k/3.14);
    return res;
}

double MyFormulsDll::dia_tnd(){//что? сокращаются
    double res;
    res=0.74;
    return res;
}

double MyFormulsDll::work_for_tnd(double koeff_knd_kvd, double work_for_ventilator, double koeff_kc){
    double res;
    res= ((koeff_knd_kvd+1)*work_for_ventilator)/koeff_kc;
    return res;
}

double MyFormulsDll::temp_for_tnd(double tvd_temperature,
                                  double work_for_tnd, double K_g, double R_g){
    double res;
    res=tvd_temperature-work_for_tnd/((K_g*R_g)/(K_g-1));
    return res;
}

double MyFormulsDll::ratio_tnd(double work_for_tvd, double K_g,
                               double R_g, double tvd_temperature,
                               double kpd_tnd){
    double res, x;
    x=K_g/(K_g-1);
    res=1/(pow(1-(work_for_tvd/(x*R_g*tvd_temperature*kpd_tnd)), x));
    return res;
}

double MyFormulsDll::all_press_tnd(){// не заданы параметры Р_ТВДвых
    double res;
    res=301579.87;
    return res;
}

double MyFormulsDll::rash_tnd(double K_g, double speed_tnd){
    double res,y, x, p;
     x=1/(K_g-1);
     p=K_g+1;
     y=(K_g-1)/(K_g+1);
     res=pow((p/2), x)*(pow(1-y*pow(speed_tnd,2),x))*speed_tnd;
     return res;
}

double MyFormulsDll::area_tnd(double gas_tnd, double cold_air_tnd,
                              double G_v_kvd, double temp_for_tnd,
                              double S_g, double all_press_tnd, double rash_tnd,
                              double alpha_tnd){
    double res;
    res=((gas_tnd+cold_air_tnd*G_v_kvd)*sqrt(temp_for_tnd))/(S_g*all_press_tnd*rash_tnd*sin(alpha_tnd));
    return res;
}

double MyFormulsDll::high_tnd(double dia_tnd, double area_tnd){
    double res;
    res=dia_tnd/2-sqrt(pow(dia_tnd/4, 2)-area_tnd/3.14);
    return res;
}

double MyFormulsDll::middle_tnd(double dia_tnd, double area_tnd){
    double res;
    res=sqrt(pow(dia_tnd,2)-2*area_tnd/3.14);
    return res;
}

double MyFormulsDll::area_tnd_circle(double gas_tnd,
                                    double tvd_temperature,double S_g,
                                     double rate_tvd,double koeff_knd_kvd){
    double res;
    res=(gas_tnd*sqrt(tvd_temperature))/(S_g*tvd_temperature*rate_tvd*koeff_knd_kvd);
    return res;
}

double MyFormulsDll::mid_dia_tnd(){
    double res=0.6;
    return res;
}
double MyFormulsDll::input_tnd(double mid_dia_tnd, double area_tnd_circle){
    double res;
    res=sqrt(pow(mid_dia_tnd,2)+2*area_tnd_circle/3.14);
    return res;
}

double MyFormulsDll::output_tnd(double mid_dia_tnd, double area_tnd_circle){
    double res;
    res=sqrt(pow(mid_dia_tnd,2)-2*area_tnd_circle/3.14);
    return res;
}

double MyFormulsDll::polusumma(){
    double res=0.6;
    return res;
}

double MyFormulsDll::polusumma_knd(double knd_dia, double dia_knd_out){
    double res;
    res=(knd_dia+dia_knd_out)/2;
    return res;
}

double MyFormulsDll::steps_tnd(double ratio_knd_tnd, double Z_vent,double m,
                               double polusumma, double polusumma_knd){
    double res;
    res=(pow(ratio_knd_tnd,2)*Z_vent*(m+1))/pow((polusumma/polusumma_knd),2);
    return res;
}
double MyFormulsDll::krug_speed(double mid_dia_tnd, double n_vent){
    double res;
    res=(3.14*mid_dia_tnd*n_vent)/60;
    return res;
}

double MyFormulsDll::param_nag(double krug_speed, double steps_tnd, double kpd_tnd,
                               double work_for_tnd){
 double res;
 res=krug_speed*sqrt((steps_tnd*kpd_tnd)/(2*work_for_tnd));
 return res;
}

double MyFormulsDll::temp_padd_tnd(double temp_for_tnd, double krug_speed, double adiabatt, double gas_ker){
    double temp;
    temp = 0.95 * (temp_for_tnd + (pow(krug_speed,2)*(adiabatt - 1)) /( 2 * adiabatt*gas_ker));
    return temp;
}

double MyFormulsDll::volt(double sett_m, double area_tnd,double koeff_tvd,
                          double n_vent){
    double res;
    res=8.2*sett_m*area_tnd*koeff_tvd*n_vent;
    return res;
}

double MyFormulsDll::zapas_steps(double limit_tnd_baddle, double volt){
    double res;
    res=limit_tnd_baddle/volt;
    return res;
}

double MyFormulsDll::temp_for_tnd2(double temp_for_tnd, double krug_speed,
                                  double K_g, double R_g){
    double res;
    res=temp_for_tnd+(pow(krug_speed,2)*(K_g-1))/(2*K_g*R_g);
    return res;
}

double MyFormulsDll::temp_paddl_tnd(double temp_for_tnd, double speed_tvd_input,
                                    double temp_cold){
    double res;
    res=temp_for_tnd-speed_tvd_input*(temp_for_tnd-temp_cold);
    return res;
}


