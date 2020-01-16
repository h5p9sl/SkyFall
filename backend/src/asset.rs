use std::path::PathBuf;

pub struct Asset {}

impl Asset {
    fn find_asset_dir() -> PathBuf {
        let result = find_folder::Search::ParentsThenKids(3, 3).for_folder("res");
        if let Ok(assets) = result {
            assets
        } else {
            panic!("Could not find resources!");
        }
    }

    fn app_asset_dir(category: String, name: String) -> String {
        let mut assets = Asset::find_asset_dir();
        assets.push(category);
        assets.push(name);
        assets.to_str().unwrap().to_string()
    }

    pub fn font<S: Into<String>>(name: S) -> String {
        Asset::app_asset_dir("fonts".into(), name.into())
    }

    pub fn music<S: Into<String>>(name: S) -> String {
        Asset::app_asset_dir("music".into(), name.into())
    }
}
