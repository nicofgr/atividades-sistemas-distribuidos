use serde::{Deserialize, Serialize};
use sqlx::FromRow;
use validator::Validate;

#[derive(Debug, Serialize, FromRow)]
pub struct Star {
    pub id: i64,
    pub name: String,
    pub mass: f32,
    pub surface_temperature: f32,
    pub luminosity: f32,
    pub radius: f32,
}

#[derive(Debug, Deserialize, Validate)]
pub struct CreateStar {
    #[validate(length(min = 1))]
    pub name: String,

    #[validate(range(min = 0.0))]
    pub mass: f32,

    #[validate(range(min = 0.0))]
    pub surface_temperature: f32,

    #[validate(range(min = 0.0))]
    pub luminosity: f32,

    #[validate(range(min = 0.0))]
    pub radius: f32,
}

#[derive(Debug, Deserialize, Validate)]
pub struct UpdateStar {
    #[validate(length(min = 1))]
    pub name: String,
    #[validate(range(min = 0.0))]
    pub mass: f32,
    #[validate(range(min = 0.0))]
    pub surface_temperature: f32,
    #[validate(range(min = 0.0))]
    pub luminosity: f32,
    #[validate(range(min = 0.0))]
    pub radius: f32,
}



#[derive(Debug, Serialize, FromRow)]
pub struct Observation {
    pub id: i64,
    pub telescope: String,
    pub date: String,
    pub starid: i64,
}

#[derive(Debug, Deserialize, Validate)]
pub struct CreateObservation {
    #[validate(length(min = 1))]
    pub telescope: String,
    pub date: String,
    pub starid: i64,
}
