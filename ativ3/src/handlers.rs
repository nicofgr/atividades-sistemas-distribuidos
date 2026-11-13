use axum::{
    extract::{Path, State},
    http::StatusCode,
    Json,
};

use axum_valid::Valid;

use crate::{
    models::{CreateStar, UpdateStar, Star, Observation, CreateObservation},
    state::AppState,
};

pub async fn create_star(
    State(state): State<AppState>,
        Valid(Json(payload)): Valid<Json<CreateStar>>,
) -> (StatusCode, Json<Star>) {
    let star = sqlx::query_as::<_, Star>(
        "INSERT INTO stars (name, mass, surface_temperature, luminosity, radius)
         VALUES (?, ?, ?, ?, ?)
         RETURNING id, name, mass, surface_temperature, luminosity, radius",
    )
    .bind(payload.name)
    .bind(payload.mass)
    .bind(payload.surface_temperature)
    .bind(payload.luminosity)
    .bind(payload.radius)
    .fetch_one(&state.db)
    .await
    .unwrap();

    (StatusCode::CREATED, Json(star))
}


pub async fn get_stars(
    State(state): State<AppState>,
) -> Json<Vec<Star>> {
    let stars = sqlx::query_as::<_, Star>(
        "SELECT id, name, mass, surface_temperature, luminosity, radius FROM stars",
    )
    .fetch_all(&state.db)
    .await
    .unwrap();

    Json(stars)
}

pub async fn get_star_by_id(
    Path(id): Path<i64>,
    State(state): State<AppState>,
) -> Result<Json<Star>, StatusCode> {
    let star = sqlx::query_as::<_, Star>(
        "SELECT id, name, mass, surface_temperature, luminosity, radius FROM stars WHERE id = ?",
    )
    .bind(id)
    .fetch_optional(&state.db)
    .await
    .unwrap();

    match star {
        Some(star) => Ok(Json(star)),
        None => Err(StatusCode::NOT_FOUND),
    }
}

pub async fn update_star(
    Path(id): Path<i64>,
    State(state): State<AppState>,
    Valid(Json(payload)): Valid<Json<UpdateStar>>,
) -> Result<Json<Star>, StatusCode> {
    let star = sqlx::query_as::<_, Star>(
        "UPDATE stars
         SET name = ?, mass = ?, surface_temperature = ?, luminosity = ?, radius = ?
         WHERE id = ?
         RETURNING id, name, mass, surface_temperature, luminosity, radius",
    )
    .bind(payload.name)
    .bind(payload.mass)
    .bind(payload.surface_temperature)
    .bind(payload.luminosity)
    .bind(payload.radius)
    .bind(id)
    .fetch_optional(&state.db)
    .await
    .unwrap();

    match star {
        Some(star) => Ok(Json(star)),
        None => Err(StatusCode::NOT_FOUND),
    }
}

pub async fn delete_star(
    Path(id): Path<i64>,
    State(state): State<AppState>,
) -> StatusCode {
    let result = sqlx::query(
        "DELETE FROM stars WHERE id = ?",
    )
    .bind(id)
    .execute(&state.db)
    .await
    .unwrap();

    if result.rows_affected() == 0 {
        StatusCode::NOT_FOUND
    } else {
        StatusCode::NO_CONTENT
    }
}

// OBSERVATIONS ======================

pub async fn create_observation(
    State(state): State<AppState>,
        Valid(Json(payload)): Valid<Json<CreateObservation>>,
) -> Result<(StatusCode, Json<Observation>), (StatusCode, String)> {
    let observation = sqlx::query_as::<_, Observation>(
        "INSERT INTO observations (telescope, date, starid)
         VALUES (?, ?, ?)
         RETURNING id, telescope, date, starid",
    )
    .bind(payload.telescope)
    .bind(payload.date)
    .bind(payload.starid)
    .fetch_one(&state.db)
    .await
    .map_err(|e| {
    (StatusCode::BAD_REQUEST, format!("Database error: {}", e))
})?;

    Ok((StatusCode::CREATED, Json(observation)))
}

pub async fn get_observations(
    State(state): State<AppState>,
) -> Json<Vec<Observation>> {
    let observation = sqlx::query_as::<_, Observation>(
        "SELECT id, telescope, date, starid FROM observations",
    )
    .fetch_all(&state.db)
    .await
    .unwrap();

    Json(observation)
}

pub async fn get_observation_by_id(
    Path(id): Path<i64>,
    State(state): State<AppState>,
) -> Result<Json<Observation>, StatusCode> {
    let observation = sqlx::query_as::<_, Observation>(
        "SELECT id, telescope, date, starid FROM observations WHERE id = ?",
    )
    .bind(id)
    .fetch_optional(&state.db)
    .await
    .unwrap();

    match observation {
        Some(observation) => Ok(Json(observation)),
        None => Err(StatusCode::NOT_FOUND),
    }
}
