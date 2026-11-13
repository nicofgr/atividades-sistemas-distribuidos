mod db;
mod handlers;
mod models;
mod state;

use axum::{
    routing::{get, post},
    Router,
};

use db::{create_table, init_db};
use handlers::{
    create_star,
    delete_star,
    get_star_by_id,
    get_stars,
    update_star,
    create_observation,
    get_observation_by_id,
    get_observations,
};
use state::AppState;

#[tokio::main]
async fn main() {
    let pool = init_db().await;

    create_table(&pool).await;

    let state = AppState { db: pool };

    let app = Router::new()
        .route("/stars", post(create_star).get(get_stars))
        .route(
            "/stars/{id}",
            get(get_star_by_id)
                .put(update_star)
                .delete(delete_star),
        )
        .route("/observations", post(create_observation).get(get_observations))
        .route(
            "/observations/{id}",
            get(get_observation_by_id)
        )
        .with_state(state);

    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000")
        .await
        .unwrap();

    println!("Server running on http://localhost:3000");

    axum::serve(listener, app).await.unwrap();
}
