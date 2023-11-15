#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct wmWindowManager;
bool wm_xr_handle_sculpt_cursor_info(wmWindowManager *wm,
                                     float loc[3],
                                     float scene_loc[3],
                                     float norm[3],
                                     float active_obj_wmat[4][4],
                                     float radius,
                                     float outline_col[3],
                                     float outline_alpha,
                                     float brush_alpha,
                                     bool active);

bool wm_xr_handle_set_sculpt_cursor_active(wmWindowManager *wm, bool active);

#ifdef __cplusplus
}
#endif
