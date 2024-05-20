use raylib_ffi::Vector2;

#[macro_export]
macro_rules! return_wrap {
    ($($fn_name:ident -> $type:ident = $equivalent:ident),* $(,)?) => {
        $(
            #[inline]
            pub fn $fn_name() -> $type {
                unsafe { raylib_ffi::$equivalent() }
            }
        )*
    };
}

return_wrap! {
    screen_width -> i32 = GetScreenWidth,
    screen_height -> i32 = GetScreenHeight,
    get_current_monitor -> i32 = GetCurrentMonitor,
    frame_time -> f32 = GetFrameTime,
}