pub struct Font<'a> {
    cache: GlyphCache<'a>,
}

impl Default for Font {
    fn default() -> Font<'static> {
        let path = "default.ttf";
        Font {
            cache: GlyphCache::new(path, TextureSettings::new()),
        }
    }
}

impl Font {

}
