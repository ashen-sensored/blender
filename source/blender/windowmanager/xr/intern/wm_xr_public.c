#include "BKE_callbacks.h"
#include "BKE_context.h"
#include "BKE_global.h"
#include "BKE_idprop.h"
#include "BKE_main.h"
#include "BKE_scene.h"
#include "BKE_screen.h"

#include "BLI_listbase.h"
#include "BLI_math.h"

#include "DEG_depsgraph.h"
#include "DEG_depsgraph_query.h"

#include "DNA_camera_types.h"
#include "DNA_space_types.h"

#include "DRW_engine.h"

#include "ED_screen.h"
#include "ED_space_api.h"

#include "GHOST_C-api.h"

#include "GPU_batch.h"
#include "GPU_viewport.h"

#include "MEM_guardedalloc.h"

#include "PIL_time.h"

#include "WM_api.h"
#include "WM_types.h"

#include "wm_event_system.h"
#include "wm_surface.h"
#include "wm_window.h"
#include "wm_xr_intern.h"

bool wm_xr_handle_sculpt_cursor_info(wmWindowManager *wm,
                                     float loc[3],
                                     float scene_loc[3],
                                     float norm[3],
                                     float active_obj_wmat[4][4],
                                     float radius,
                                     float outline_col[3],
                                     float outline_alpha,
                                     float brush_alpha,
                                     bool active)
{
  wmXrPaintCursorData *cursor_data = &wm->xr.runtime->session_state.paint_cursor_data;

  if (active) {
    cursor_data->cursor_location[0] = loc[0];
    cursor_data->cursor_location[1] = loc[1];
    cursor_data->cursor_location[2] = loc[2];
    cursor_data->cursor_scene_location[0] = scene_loc[0];
    cursor_data->cursor_scene_location[1] = scene_loc[1];
    cursor_data->cursor_scene_location[2] = scene_loc[2];
    cursor_data->cursor_normal[0] = norm[0];
    cursor_data->cursor_normal[1] = norm[1];
    cursor_data->cursor_normal[2] = norm[2];
    copy_m4_m4(cursor_data->active_object_to_world, active_obj_wmat);
    cursor_data->cursor_radius = radius;
    copy_v3_v3(cursor_data->outline_col, outline_col);
    cursor_data->outline_alpha = outline_alpha;
    cursor_data->brush_alpha = brush_alpha;
    cursor_data->cursor_visible = true;
  }
  else {
    cursor_data->cursor_visible = false;
  }

  return true;
}

bool wm_xr_handle_set_sculpt_cursor_active(wmWindowManager *wm, bool active)
{
  wmXrPaintCursorData *cursor_data = &wm->xr.runtime->session_state.paint_cursor_data;

  cursor_data->cursor_visible = active;

  return true;
}

