pub struct Window {
    title: String,
    width: i32,
    height: i32,
    flags: u32,
}

impl Window {
    pub fn new(title: &str) -> Self {
        Self {title: format!("{title}\0"), width: 800, height: 600, flags: 0}
    }
    pub fn resizable(mut self) -> Self {
        self.flags |= raylib_ffi::enums::ConfigFlags::WindowResizable as u32;
        self
    }
    pub fn size(mut self, w: i32, h: i32) -> Self {
        self.width = w;
        self.height = h;
        self
    }
    pub fn init(self) -> Self {
        unsafe {
            raylib_ffi::SetConfigFlags(self.flags);
            raylib_ffi::InitWindow(self.width, self.height, self.title.as_ptr() as *const i8);
        }
        self
    }

    pub fn should_close(&self) -> bool {
        unsafe {
            raylib_ffi::WindowShouldClose()
        }
    }
}

impl Drop for Window {
    fn drop(&mut self) {
        unsafe {
            raylib_ffi::CloseWindow();
        }
    }
}