#include "lvgl/lvgl.h"

static lv_obj_t *tv;
static lv_obj_t *t1;
static lv_obj_t *t2;
static lv_obj_t *t3;
static lv_obj_t *gauge_cpu_usage;
static lv_obj_t *lmeter_ram_usage;
static lv_obj_t *label_ram_usage;

static lv_style_t style_box;

static void tab1_create(lv_obj_t * parent);
static void tab2_create(lv_obj_t * parent);
static void tab3_create(lv_obj_t * parent);

void lv_create() {

    // tab bar
    tv = lv_tabview_create(lv_scr_act(), NULL);
    //lv_obj_set_style_local_pad_left(tv, LV_TABVIEW_PART_TAB_BG, LV_STATE_DEFAULT, LV_HOR_RES / 2);
    lv_tabview_set_btns_pos(tv, LV_TABVIEW_TAB_POS_NONE);

    // tabs
    t1 = lv_tabview_add_tab(tv, "Controls");
    t2 = lv_tabview_add_tab(tv, "Visuals");
    t3 = lv_tabview_add_tab(tv, "Selectors");

    lv_style_init(&style_box);
    lv_style_set_value_align(&style_box, LV_STATE_DEFAULT, LV_ALIGN_OUT_TOP_LEFT);
    lv_style_set_value_ofs_y(&style_box, LV_STATE_DEFAULT, - LV_DPX(10));
    lv_style_set_margin_top(&style_box, LV_STATE_DEFAULT, LV_DPX(30));

    tab1_create(t1);
    tab2_create(t2);
    tab3_create(t3);
}


static void tab1_create(lv_obj_t * parent) {
    
    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
    
    lv_coord_t grid_w_meter;
    if (disp_size <= LV_DISP_SIZE_SMALL) grid_w_meter = lv_page_get_width_grid(parent, 1, 1);
    else if (disp_size <= LV_DISP_SIZE_MEDIUM) grid_w_meter = lv_page_get_width_grid(parent, 2, 1);
    else grid_w_meter = lv_page_get_width_grid(parent, 3, 1);

    lv_coord_t meter_h = lv_page_get_height_fit(parent);

    lv_coord_t meter_size = LV_MATH_MIN(grid_w_meter, meter_h);
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);

    // arc
    lv_obj_t *arc = lv_arc_create(parent, NULL);
    lv_obj_set_drag_parent(arc, true);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_rotation(arc, 270);
    lv_arc_set_angles(arc, 0, 0);
    lv_obj_set_size(arc,  meter_size, meter_size);
    lv_obj_add_style(arc, LV_ARC_PART_BG, &style_box);
    lv_obj_set_style_local_value_str(arc, LV_ARC_PART_BG, LV_STATE_DEFAULT, "Arc");

    lv_obj_t *label = lv_label_create(arc, NULL);
    lv_obj_align(label, arc, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());

}

static void tab2_create(lv_obj_t * parent) {


    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
    
    lv_coord_t grid_w_meter;
    if (disp_size <= LV_DISP_SIZE_SMALL) grid_w_meter = lv_page_get_width_grid(parent, 1, 1);
    else if (disp_size <= LV_DISP_SIZE_MEDIUM) grid_w_meter = lv_page_get_width_grid(parent, 2, 1);
    else grid_w_meter = lv_page_get_width_grid(parent, 3, 1);

    lv_coord_t meter_h = lv_page_get_height_fit(parent);

    lv_coord_t meter_size = LV_MATH_MIN(grid_w_meter, meter_h);
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);

    // line meter cpu
    /*
    lmeter_cpu_usage = lv_linemeter_create(parent, NULL);
    lv_obj_set_drag_parent(lmeter_cpu_usage, true);
    lv_linemeter_set_value(lmeter_cpu_usage, 50);
    lv_obj_set_size(lmeter_cpu_usage, meter_size, meter_size);
    lv_obj_add_style(lmeter_cpu_usage, LV_LINEMETER_PART_MAIN, &style_box);
    lv_obj_set_style_local_value_str(lmeter_cpu_usage, LV_LINEMETER_PART_MAIN, LV_STATE_DEFAULT, "CPU usage");

    lv_obj_t *label1 = lv_label_create(lmeter_cpu_usage, NULL);
    lv_obj_align(label1, lmeter_cpu_usage, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_local_text_font(label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
    */

    // gauge cpu
    gauge_cpu_usage = lv_gauge_create(parent, NULL);
    lv_obj_set_drag_parent(gauge_cpu_usage, true);
    lv_obj_set_size(gauge_cpu_usage, meter_size, meter_size);
    lv_obj_add_style(gauge_cpu_usage, LV_GAUGE_PART_MAIN, &style_box);
    lv_obj_set_style_local_value_str(gauge_cpu_usage, LV_GAUGE_PART_MAIN, LV_STATE_DEFAULT, "CPU usage");

    // line meter ram
    lmeter_ram_usage = lv_linemeter_create(parent, NULL);
    lv_obj_set_drag_parent(lmeter_ram_usage, true);
    lv_linemeter_set_value(lmeter_ram_usage, 50);
    lv_obj_set_size(lmeter_ram_usage, meter_size, meter_size);
    lv_obj_add_style(lmeter_ram_usage, LV_LINEMETER_PART_MAIN, &style_box);
    lv_obj_set_style_local_value_str(lmeter_ram_usage, LV_LINEMETER_PART_MAIN, LV_STATE_DEFAULT, "RAM usage");

    label_ram_usage = lv_label_create(lmeter_ram_usage, NULL);
    lv_obj_align(label_ram_usage, lmeter_ram_usage, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_local_text_font(label_ram_usage, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());

    //lv_img_set_src(img, "S:png/");

}

void lv_set_cpu_usage(uint16_t num) {
    lv_gauge_set_value(gauge_cpu_usage, 0, num);
}

void lv_set_ram_usage(uint16_t num) {
    lv_linemeter_set_value(lmeter_ram_usage, num);
    lv_label_set_text_fmt(label_ram_usage, "%d", num);
}


static void list_btn_event_handler(lv_obj_t * btn, lv_event_t event){
    // empty
}

static void tab3_create(lv_obj_t * parent)
{
    lv_coord_t hres = lv_disp_get_hor_res(NULL);

    static lv_style_t style_page;
    lv_style_init(&style_page);

    lv_style_set_bg_opa(&style_page, LV_STATE_DEFAULT, LV_OPA_100);
    lv_style_set_pad_top(&style_page, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_bottom(&style_page, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_left(&style_page, LV_STATE_DEFAULT, 5);
    lv_style_set_pad_right(&style_page, LV_STATE_DEFAULT, 5);

    lv_obj_add_style(parent, LV_PAGE_PART_BG, &style_page);
    lv_obj_add_style(parent, LV_PAGE_PART_SCROLLABLE, &style_page);

    lv_page_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);

    /*Create styles for the buttons*/
    static lv_style_t style_btn;
    lv_style_init(&style_btn);

    lv_style_set_bg_color(&style_btn, LV_BTN_STATE_RELEASED, lv_color_hex3(0x333));
    lv_style_set_bg_grad_color(&style_btn, LV_BTN_STATE_RELEASED, LV_COLOR_BLACK);
    lv_style_set_border_color(&style_btn, LV_BTN_STATE_RELEASED, LV_COLOR_SILVER);
    lv_style_set_border_width(&style_btn, LV_BTN_STATE_RELEASED, 1);
    lv_style_set_border_opa(&style_btn, LV_BTN_STATE_RELEASED, LV_OPA_50);
    lv_style_set_radius(&style_btn, LV_BTN_STATE_RELEASED, 0);

    lv_style_set_bg_color(&style_btn, LV_BTN_STATE_PRESSED, lv_color_make(0x55, 0x96, 0xd8));
    lv_style_set_bg_grad_color(&style_btn, LV_BTN_STATE_PRESSED, lv_color_make(0x37, 0x62, 0x90));
    lv_style_set_text_color(&style_btn, LV_BTN_STATE_PRESSED, lv_color_make(0xbb, 0xd5, 0xf1));

    lv_obj_t * list = lv_list_create(parent, NULL);
    lv_obj_set_height(list, 2 * lv_obj_get_height(parent) / 3);

    static lv_style_t style_list;
    lv_style_init(&style_list);
    lv_style_set_bg_opa(&style_list, LV_STATE_DEFAULT, LV_OPA_100);
    lv_style_set_pad_left(&style_list, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_right(&style_list, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_top(&style_list, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_bottom(&style_list, LV_STATE_DEFAULT, 0);

    lv_obj_add_style(list, LV_LIST_PART_BG, &style_list);
    lv_obj_add_style(list, LV_LIST_PART_SCROLLABLE, &style_list);

    lv_obj_align(list, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 4);

    lv_obj_t * list_btn;
    list_btn = lv_list_add_btn(list, LV_SYMBOL_FILE, "New");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, "Open");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_TRASH, "Delete");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_EDIT, "Edit");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_SAVE, "Save");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_WIFI, "WiFi");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_GPS, "GPS");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    lv_obj_t * mbox = lv_msgbox_create(parent, NULL);
    lv_msgbox_set_text(mbox, "Click a button to copy its text to the Text area ");
    lv_obj_set_width(mbox, hres - LV_DPI);
    static const char * mbox_btns[] = {"Got it", ""};
    lv_msgbox_add_btns(mbox, mbox_btns);    /*The default action is close*/
    lv_obj_align(mbox, parent, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 2);
}

