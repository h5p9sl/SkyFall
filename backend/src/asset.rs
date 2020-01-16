use std::path::PathBuf;

pub struct Asset {}

impl Asset {
    fn find_asset_dir() -> PathBuf {
        let result = find_folder::Search::ParentsThenKids(3, 3)
            .for_folder("res");
        if let Ok(assets) = result {
            assets
        } else {
            panic!("Could not find resources!");
        }
    }

    pub fn font<S>(name: S) -> Option<String>
    where
        S: Into<String>,
    {
        let mut assets = Asset::find_asset_dir();
        assets.push("fonts");
        assets.push(name.into());
        Some(assets.to_str()
             .unwrap()
             .to_string()
            )
    }
}
