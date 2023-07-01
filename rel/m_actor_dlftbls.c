#include "m_actor_dlftbls.h"

#include "m_player_call.h"
#include "ac_sample.h"
#include "ac_airplane.h"
#include "ac_animal_logo.h"
#include "ac_arrange_ftr.h"
#include "ac_arrange_room.h"
#include "ac_ball.h"
#include "ac_balloon.h"
#include "ac_birth_control.h"
#include "ac_boat_demo.h"
#include "ac_boxManager.h"
#include "ac_boxMove.h"
#include "ac_boxTrick01.h"
#include "ac_broker_design.h"
#include "ac_cottage.h"
#include "ac_cottage.h"
#include "ac_effectbg.h"
#include "ac_event_manager.h"
#include "ac_field_draw.h"
#include "ac_fieldm_draw.h"
#include "ac_flag.h"
#include "ac_garagara.h"
#include "ac_gyo_kage.h"
#include "ac_gyo_release.h"
#include "ac_handOverItem.h"
#include "ac_haniwa.h"
#include "ac_hatumode_control.h"
#include "ac_house_clock.h"
#include "ac_intro_demo.h"
#include "ac_kamakura_indoor.h"
#include "ac_lighthouse_switch.h"
#include "ac_mailbox.h"
#include "ac_mbg.h"
#include "ac_misin.h"
#include "ac_mural.h"
#include "ac_museum_fossil.h"
#include "ac_museum_picture.h"
#include "ac_museum_fish.h"
#include "ac_museum_indoor.h"
#include "ac_museum_insect.h"
#include "ac_my_indoor.h"
#include "ac_my_room.h"
#include "ac_needlework_indoor.h"
#include "ac_present_demo.h"
#include "ac_psnowman.h"
#include "ac_pterminal.h"
#include "ac_quest_manager.h"
#include "ac_reset_demo.h"
#include "ac_ride_off_demo.h"
#include "ac_rope.h"
#include "ac_set_manager.h"
#include "ac_set_npc_manager.h"
#include "ac_shop_design.h"
#include "ac_shop_goods.h"
#include "ac_shop_indoor.h"
#include "ac_shop_level.h"
#include "ac_shop_manekin.h"
#include "ac_shop_umbrella.h"
#include "ac_sign.h"
#include "ac_snowman.h"
#include "ac_t_anrium1.h"
#include "ac_t_bag1.h"
#include "ac_t_bag2.h"
#include "ac_t_biscus1.h"
#include "ac_t_biscus2.h"
#include "ac_t_biscus3.h"
#include "ac_t_biscus4.h"
#include "ac_t_cobra1.h"
#include "ac_t_cracker.h"
#include "ac_t_flag.h"
#include "ac_t_hanabi.h"
#include "ac_t_hasu1.h"
#include "ac_t_hat1.h"
#include "ac_t_hat2.h"
#include "ac_t_hat3.h"
#include "ac_t_keitai.h"
#include "ac_t_npc_sao.h"
#include "ac_t_pistol.h"
#include "ac_t_rei1.h"
#include "ac_t_rei2.h"
#include "ac_t_tama.h"
#include "ac_t_tumbler.h"
#include "ac_t_umbrella.h"
#include "ac_t_utiwa.h"
#include "ac_t_zinnia1.h"
#include "ac_t_zinnia2.h"
#include "ac_tokyoso_control.h"
#include "ac_tools.h"
#include "ac_train_door.h"
#include "ac_train_window.h"
#include "ac_tunahiki_control.h"
#include "ac_uki.h"
#include "bg_cherry_item.h"
#include "bg_item.h"
#include "bg_police_item.h"
#include "bg_post_item.h"
#include "bg_winter_item.h"
#include "bg_xmas_item.h"
#include "ef_effect_control.h"
#include "ef_lamp_light.h"
#include "ef_room_sunshine.h"
#include "ef_room_sunshine_police.h"
#include "ef_room_sunshine_posthouse.h"
#include "ef_room_sunshine_museum.h"
#include "ef_room_sunshine_minsect.h"
#include "ev_cherry_manager.h"
#include "ac_house_goki.h"
#include "ac_ant.h"
#include "ac_bee.h"
#include "ac_fuusen.h"
#include "ac_aprilfool_control.h"
#include "ac_groundhog_control.h"
#include "ac_mscore_control.h"
#include "ac_countdown_npc0.h"
#include "ac_countdown_npc1.h"
#include "ac_ev_angler.h"
#include "ac_ev_artist.h"
#include "ac_ev_broker.h"
#include "ac_ev_broker2.h"
#include "ac_ev_carpetPeddler.h"
#include "ac_ev_castaway.h"
#include "ac_ev_designer.h"
#include "ac_ev_dokutu.h"
#include "ac_dummy.h"
#include "ac_ev_dozaemon.h"
#include "ac_ev_ghost.h"
#include "ac_ev_gypsy.h"
#include "ac_ev_kabuPeddler.h"
#include "ac_ev_miko.h"
#include "ac_ev_pumpkin.h"
#include "ac_ev_santa.h"
#include "ac_ev_soncho.h"
#include "ac_ev_soncho2.h"
#include "ac_ev_speech_soncho.h"
#include "ac_ev_yomise.h"
#include "ac_go_home_npc.h"
#include "ac_halloween_npc.h"
#include "ac_hanabi_npc0.h"
#include "ac_hanabi_npc1.h"
#include "ac_hanami_npc0.h"
#include "ac_hanami_npc1.h"
#include "ac_hatumode_npc0.h"
#include "ac_kamakura_npc0.h"
#include "ac_normal_npc.h"
#include "ac_npc.h"
#include "ac_npc2.h"
#include "ac_npc_conv_master.h"
#include "ac_npc_curator.h"
#include "ac_npc_depart_master.h"
#include "ac_npc_engineer.h"
#include "ac_npc_guide.h"
#include "ac_npc_guide2.h"
#include "ac_npc_majin.h"
#include "ac_npc_majin2.h"
#include "ac_npc_majin3.h"
#include "ac_npc_majin4.h"
#include "ac_npc_majin5.h"
#include "ac_npc_mamedanuki.h"
#include "ac_npc_mask_cat.h"
#include "ac_npc_mask_cat2.h"
#include "ac_npc_needlework.h"
#include "ac_npc_p_sel.h"
#include "ac_npc_p_sel2.h"
#include "ac_npc_police.h"
#include "ac_npc_police2.h"
#include "ac_npc_post_girl.h"
#include "ac_npc_post_man.h"
#include "ac_npc_rcn_guide.h"
#include "ac_npc_rcn_guide2.h"
#include "ac_npc_restart.h"
#include "ac_npc_rtc.h"
#include "ac_npc_sendo.h"
#include "ac_npc_shasho.h"
#include "ac_npc_shop_master.h"
#include "ac_npc_shop_mastersp.h"
#include "ac_npc_sleep_obaba.h"
#include "ac_npc_soncho.h"
#include "ac_npc_station_master.h"
#include "ac_npc_super_master.h"
#include "ac_npc_totakeke.h"
#include "ac_present_npc.h"
#include "ac_taisou_npc0.h"
#include "ac_tamaire_npc0.h"
#include "ac_tamaire_npc1.h"
#include "ac_tokyoso_npc0.h"
#include "ac_tokyoso_npc1.h"
#include "ac_tukimi_npc0.h"
#include "ac_tukimi_npc1.h"
#include "ac_tunahiki_npc0.h"
#include "ac_tunahiki_npc1.h"
#include "ac_turi_npc0.h"
#include "ac_groundhog_npc0.h"
#include "ac_harvest_npc0.h"
#include "ac_harvest_npc1.h"
#include "ac_npc_hem.h"
#include "ac_ev_majin.h"
#include "ac_ev_turkey.h"
#include "ac_insect.h"
#include "ac_gyoei.h"
#include "ac_boat.h"
#include "ac_br_shop.h"
#include "ac_bridge_a.h"
#include "ac_buggy.h"
#include "ac_conveni.h"
#include "ac_count02.h"
#include "ac_countdown.h"
#include "ac_depart.h"
#include "ac_douzou.h"
#include "ac_dump.h"
#include "ac_fallS.h"
#include "ac_fallSESW.h"
#include "ac_ghog.h"
#include "ac_goza.h"
#include "ac_house.h"
#include "ac_htable.h"
#include "ac_kago.h"
#include "ac_kamakura.h"
#include "ac_koinobori.h"
#include "ac_lotus.h"
#include "ac_mikanbox.h"
#include "ac_mikuji.h"
#include "ac_museum.h"
#include "ac_my_house.h"
#include "ac_nameplate.h"
#include "ac_needlework_shop.h"
#include "ac_police_box.h"
#include "ac_post_office.h"
#include "ac_radio.h"
#include "ac_reserve.h"
#include "ac_s_car.h"
#include "ac_shop.h"
#include "ac_shrine.h"
#include "ac_station.h"
#include "ac_structure.h"
#include "ac_super.h"
#include "ac_tama.h"
#include "ac_tent.h"
#include "ac_toudai.h"
#include "ac_train0.h"
#include "ac_train1.h"
#include "ac_tukimi.h"
#include "ac_turi.h"
#include "ac_windmill.h"
#include "ac_yatai.h"
#include "ac_weather.h"

#define MAKE_ACTOR_DLF(actor)\
  {0,0,NULL,NULL,NULL,&actor##_Profile, 0,0,0,0}

#define MAKE_ACTOR_NULL()\
  {0,0,NULL,NULL,NULL,NULL,0,0,0,0}


ACTOR_DLFTBL actor_dlftbls[] = {
  MAKE_ACTOR_DLF(Player),
  MAKE_ACTOR_DLF(BgItem),
  MAKE_ACTOR_DLF(Sample),
  MAKE_ACTOR_DLF(Fieldm_Draw),
  MAKE_ACTOR_DLF(Field_Draw),
  MAKE_ACTOR_DLF(Airplane),
  MAKE_ACTOR_DLF(Room_Sunshine),
  MAKE_ACTOR_DLF(Lamp_Light),
  MAKE_ACTOR_DLF(Ev_Angler),
  MAKE_ACTOR_DLF(Ball),
  MAKE_ACTOR_DLF(Haniwa),
  MAKE_ACTOR_DLF(My_Room),
  MAKE_ACTOR_DLF(Mbg),
  MAKE_ACTOR_DLF(T_Tama),
  MAKE_ACTOR_DLF(BoxManager),
  MAKE_ACTOR_DLF(BoxMove),
  MAKE_ACTOR_DLF(BoxTrick01),
  MAKE_ACTOR_DLF(Arrange_Room),
  MAKE_ACTOR_DLF(Arrange_Furniture),
  MAKE_ACTOR_DLF(TrainDoor),
  MAKE_ACTOR_DLF(T_Keitai),
  MAKE_ACTOR_DLF(Halloween_Npc),
  MAKE_ACTOR_DLF(Ev_Pumpkin),
  MAKE_ACTOR_DLF(Ride_Off_Demo),
  MAKE_ACTOR_DLF(Npc_Mamedanuki),
  MAKE_ACTOR_DLF(Hanabi_Npc0),
  MAKE_ACTOR_DLF(Hanabi_Npc1),
  MAKE_ACTOR_DLF(Snowman),
  MAKE_ACTOR_DLF(Npc_Post_Girl),
  MAKE_ACTOR_DLF(Npc_Engineer),
  MAKE_ACTOR_DLF(Npc_Majin3),
  MAKE_ACTOR_DLF(Npc_Sleep_Obaba),
  MAKE_ACTOR_DLF(Npc),
  MAKE_ACTOR_DLF(Effect_Control),
  MAKE_ACTOR_DLF(Npc2),
  MAKE_ACTOR_DLF(Kamakura_Npc0),
  MAKE_ACTOR_DLF(Npc_Post_Man),
  MAKE_ACTOR_DLF(Shop_Design),
  MAKE_ACTOR_DLF(Quest_Manager),
  MAKE_ACTOR_DLF(MailBox),
  MAKE_ACTOR_DLF(House),
  MAKE_ACTOR_DLF(Shop_Level),
  MAKE_ACTOR_DLF(Shop),
  MAKE_ACTOR_DLF(MyHouse),
  MAKE_ACTOR_DLF(Ev_Artist),
  MAKE_ACTOR_DLF(Ev_Broker),
  MAKE_ACTOR_DLF(Ev_Designer),
  MAKE_ACTOR_DLF(T_Umbrella),
  MAKE_ACTOR_DLF(Npc_Shop_Master),
  MAKE_ACTOR_DLF(Birth_Control),
  MAKE_ACTOR_DLF(Shop_Manekin),
  MAKE_ACTOR_DLF(Shop_Indoor),
  MAKE_ACTOR_DLF(Event_Manager),
  MAKE_ACTOR_DLF(Shop_Goods),
  MAKE_ACTOR_DLF(BrShop),
  MAKE_ACTOR_DLF(Weather),
  MAKE_ACTOR_DLF(Post_Office),
  MAKE_ACTOR_DLF(Npc_Guide),
  MAKE_ACTOR_DLF(Npc_Guide2),
  MAKE_ACTOR_DLF(Insect),
  MAKE_ACTOR_DLF(Station),
  MAKE_ACTOR_DLF(Ev_CarpetPeddler),
  MAKE_ACTOR_DLF(Ev_KabuPeddler),
  MAKE_ACTOR_DLF(Reserve),
  MAKE_ACTOR_DLF(HandOverItem),
  MAKE_ACTOR_DLF(Npc_Conv_Master),
  MAKE_ACTOR_DLF(Npc_Super_Master),
  MAKE_ACTOR_DLF(Npc_Depart_Master),
  MAKE_ACTOR_DLF(Tools),
  MAKE_ACTOR_DLF(Structure),
  MAKE_ACTOR_DLF(Ev_Gypsy),
  MAKE_ACTOR_DLF(Npc_Police),
  MAKE_ACTOR_DLF(Train0),
  MAKE_ACTOR_DLF(Train1),
  MAKE_ACTOR_DLF(Npc_Station_Master),
  MAKE_ACTOR_DLF(Ev_Santa),
  MAKE_ACTOR_DLF(Npc_Police2),
  MAKE_ACTOR_DLF(Police_Box),
  MAKE_ACTOR_DLF(BgPoliceItem),
  MAKE_ACTOR_DLF(BgCherryItem),
  MAKE_ACTOR_DLF(BgWinterItem),
  MAKE_ACTOR_DLF(BgXmasItem),
  MAKE_ACTOR_DLF(BgPostItem),
  MAKE_ACTOR_DLF(FallS),
  MAKE_ACTOR_DLF(FallSESW),
  MAKE_ACTOR_DLF(Ev_Broker2),
  MAKE_ACTOR_DLF(Broker_Design),
  MAKE_ACTOR_DLF(T_Utiwa),
  MAKE_ACTOR_DLF(Psnowman),
  MAKE_ACTOR_DLF(My_Indoor),
  MAKE_ACTOR_DLF(Npc_Rcn_Guide),
  MAKE_ACTOR_DLF(Intro_Demo),
  MAKE_ACTOR_DLF(Shrine),
  MAKE_ACTOR_DLF(Buggy),
  MAKE_ACTOR_DLF(T_Hanabi),
  MAKE_ACTOR_DLF(Conveni),
  MAKE_ACTOR_DLF(Super),
  MAKE_ACTOR_DLF(Depart),
  MAKE_ACTOR_DLF(Hanami_Npc0),
  MAKE_ACTOR_DLF(S_Car),
  MAKE_ACTOR_DLF(Hanami_Npc1),
  MAKE_ACTOR_DLF(Npc_P_Sel),
  MAKE_ACTOR_DLF(Npc_P_Sel2),
  MAKE_ACTOR_DLF(Npc_Rcn_Guide2),
  MAKE_ACTOR_DLF(Train_Window),
  MAKE_ACTOR_DLF(Npc_Majin4),
  MAKE_ACTOR_DLF(Kamakura),
  MAKE_ACTOR_DLF(Gyoei),
  MAKE_ACTOR_DLF(Npc_Majin),
  MAKE_ACTOR_DLF(T_NpcSao),
  MAKE_ACTOR_DLF(Ev_Soncho),
  MAKE_ACTOR_DLF(Uki),
  MAKE_ACTOR_DLF(Npc_Majin2),
  MAKE_ACTOR_DLF(Normal_Npc),
  MAKE_ACTOR_DLF(Set_Manager),
  MAKE_ACTOR_DLF(Set_Npc_Manager),
  MAKE_ACTOR_DLF(Npc_Shop_Mastersp),
  MAKE_ACTOR_DLF(Room_Sunshine_Posthouse),
  MAKE_ACTOR_DLF(Room_Sunshine_Police),
  MAKE_ACTOR_DLF(Effectbg),
  MAKE_ACTOR_DLF(Ev_Cherry_Manager),
  MAKE_ACTOR_DLF(Ev_Yomise),
  MAKE_ACTOR_DLF(Tokyoso_Npc0),
  MAKE_ACTOR_DLF(Tokyoso_Npc1),
  MAKE_ACTOR_DLF(Goza),
  MAKE_ACTOR_DLF(Radio),
  MAKE_ACTOR_DLF(Yatai),
  MAKE_ACTOR_DLF(Tokyoso_Control),
  MAKE_ACTOR_DLF(Shop_Umbrella),
  MAKE_ACTOR_DLF(Gyo_Release),
  MAKE_ACTOR_DLF(Tukimi),
  MAKE_ACTOR_DLF(Kamakura_Indoor),
  MAKE_ACTOR_DLF(Ev_Miko),
  MAKE_ACTOR_DLF(Gyo_Kage),
  MAKE_ACTOR_DLF(Mikuji),
  MAKE_ACTOR_DLF(House_Goki),
  MAKE_ACTOR_DLF(T_Cracker),
  MAKE_ACTOR_DLF(Npc_Needlework),
  MAKE_ACTOR_DLF(T_Pistol),
  MAKE_ACTOR_DLF(T_Flag),
  MAKE_ACTOR_DLF(T_Tumbler),
  MAKE_ACTOR_DLF(Tukimi_Npc0),
  MAKE_ACTOR_DLF(Tukimi_Npc1),
  MAKE_ACTOR_DLF(Needlework_Shop),
  MAKE_ACTOR_DLF(Countdown_Npc0),
  MAKE_ACTOR_DLF(Countdown_Npc1),
  MAKE_ACTOR_DLF(Turi_Npc0),
  MAKE_ACTOR_DLF(Taisou_Npc0),
  MAKE_ACTOR_DLF(Count),
  MAKE_ACTOR_DLF(Garagara),
  MAKE_ACTOR_DLF(Tamaire_Npc0),
  MAKE_ACTOR_DLF(Tamaire_Npc1),
  MAKE_ACTOR_DLF(Hatumode_Npc0),
  MAKE_ACTOR_DLF(Npc_Totakeke),
  MAKE_ACTOR_DLF(Count02),
  MAKE_ACTOR_DLF(Hatumode_Control),
  MAKE_ACTOR_DLF(Tama),
  MAKE_ACTOR_DLF(Kago),
  MAKE_ACTOR_DLF(Turi),
  MAKE_ACTOR_DLF(House_Clock),
  MAKE_ACTOR_DLF(Tunahiki_Control),
  MAKE_ACTOR_DLF(Tunahiki_Npc0),
  MAKE_ACTOR_DLF(Tunahiki_Npc1),
  MAKE_ACTOR_DLF(Koinobori),
  MAKE_ACTOR_DLF(Bee),
  MAKE_ACTOR_DLF(Nameplate),
  MAKE_ACTOR_DLF(Dump),
  MAKE_ACTOR_DLF(Rope),
  MAKE_ACTOR_DLF(Ev_Dozaemon),
  MAKE_ACTOR_DLF(Windmill),
  MAKE_ACTOR_DLF(Lotus),
  MAKE_ACTOR_DLF(Animal_Logo),
  MAKE_ACTOR_DLF(Mikanbox),
  MAKE_ACTOR_DLF(Douzou),
  MAKE_ACTOR_DLF(Npc_Rtc),
  MAKE_ACTOR_DLF(Toudai),
  MAKE_ACTOR_DLF(Npc_Restart),
  MAKE_ACTOR_DLF(Npc_Majin5),
  MAKE_ACTOR_DLF(Fuusen),
  MAKE_ACTOR_DLF(Ev_Dokutu),
  MAKE_ACTOR_DLF(Dummy),
  MAKE_ACTOR_DLF(Npc_Curator),
  MAKE_ACTOR_DLF(Museum),
  MAKE_ACTOR_DLF(Ev_Ghost),
  MAKE_ACTOR_DLF(Museum_Picture),
  MAKE_ACTOR_NULL(),
  MAKE_ACTOR_DLF(Museum_Fish),
  MAKE_ACTOR_DLF(Museum_Insect),
  MAKE_ACTOR_DLF(Bridge_A),
  MAKE_ACTOR_DLF(Room_Sunshine_Museum),
  MAKE_ACTOR_DLF(Needlework_Indoor),
  MAKE_ACTOR_DLF(Room_Sunshine_Minsect),
  MAKE_ACTOR_DLF(Museum_Fossil),
  MAKE_ACTOR_DLF(Mural),
  MAKE_ACTOR_DLF(Ac_Sign),
  MAKE_ACTOR_DLF(Ant),
  MAKE_ACTOR_DLF(Npc_Sendo),
  MAKE_ACTOR_DLF(Flag),
  MAKE_ACTOR_DLF(Present_Demo),
  MAKE_ACTOR_DLF(Present_Npc),
  MAKE_ACTOR_DLF(Boat),
  MAKE_ACTOR_DLF(Boat_Demo),
  MAKE_ACTOR_DLF(Cottage_My),
  MAKE_ACTOR_DLF(Cottage_Npc),
  MAKE_ACTOR_DLF(Ev_Soncho2),
  MAKE_ACTOR_DLF(Npc_Mask_Cat),
  MAKE_ACTOR_DLF(Npc_Mask_Cat2),
  MAKE_ACTOR_DLF(Reset_Demo),
  MAKE_ACTOR_DLF(Go_Home_Npc),
  MAKE_ACTOR_DLF(Misin),
  MAKE_ACTOR_DLF(Lighthouse_Switch),
  MAKE_ACTOR_DLF(Museum_Indoor),
  MAKE_ACTOR_DLF(T_Anrium1),
  MAKE_ACTOR_DLF(T_Biscus1),
  MAKE_ACTOR_DLF(T_Biscus2),
  MAKE_ACTOR_DLF(T_Hasu1),
  MAKE_ACTOR_DLF(T_Hat1),
  MAKE_ACTOR_DLF(T_Zinnia1),
  MAKE_ACTOR_DLF(T_Biscus3),
  MAKE_ACTOR_DLF(T_Biscus4),
  MAKE_ACTOR_DLF(T_Zinnia2),
  MAKE_ACTOR_DLF(T_Hat2),
  MAKE_ACTOR_DLF(T_Hat3),
  MAKE_ACTOR_DLF(T_Rei1),
  MAKE_ACTOR_DLF(T_Rei2),
  MAKE_ACTOR_DLF(Npc_Shasho),
  MAKE_ACTOR_DLF(T_Bag1),
  MAKE_ACTOR_DLF(T_Bag2),
  MAKE_ACTOR_DLF(Ev_Castaway),
  MAKE_ACTOR_DLF(T_Cobra1),
  MAKE_ACTOR_DLF(Balloon),
  MAKE_ACTOR_DLF(Npc_Soncho),
  MAKE_ACTOR_DLF(Aprilfool_Control),
  MAKE_ACTOR_DLF(Ev_Majin),
  MAKE_ACTOR_DLF(Harvest_Npc0),
  MAKE_ACTOR_DLF(Harvest_Npc1),
  MAKE_ACTOR_DLF(Groundhog_Control),
  MAKE_ACTOR_DLF(Ev_Speech_Soncho),
  MAKE_ACTOR_DLF(Groundhog_Npc0),
  MAKE_ACTOR_DLF(Ev_Turkey),
  MAKE_ACTOR_DLF(Ghog),
  MAKE_ACTOR_DLF(Htable),
  MAKE_ACTOR_DLF(Npc_Hem),
  MAKE_ACTOR_DLF(Tent),
  MAKE_ACTOR_DLF(Pterminal),
  MAKE_ACTOR_DLF(Mscore_Control)
};

int actor_dlftbls_num;

extern void actor_dlftbls_init() {
  actor_dlftbls_num = 246;
}

extern void actor_dlftbls_cleanup() {
  actor_dlftbls_num = 0;
}
