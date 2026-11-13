use sqlx::sqlite::{SqliteConnectOptions, SqlitePoolOptions};
use sqlx::SqlitePool;
use std::str::FromStr;

pub async fn init_db() -> SqlitePool {
    let options = SqliteConnectOptions::from_str("sqlite:stars.db")
        .unwrap()
        .create_if_missing(true);

    SqlitePoolOptions::new()
        .max_connections(5)
        .connect_with(options)
        .await
        .unwrap()
}

pub async fn create_table(pool: &SqlitePool) {
    sqlx::query(
        "CREATE TABLE IF NOT EXISTS stars(
                    id                         INTEGER   PRIMARY KEY AUTOINCREMENT,
                    name                       CHAR(20)  NOT NULL,
                    mass                       FLOAT     NOT NULL,
                    surface_temperature        FLOAT     NOT NULL,
                    luminosity                 FLOAT     NOT NULL,
                    radius                     FLOAT     NOT NULL )",
    )
    .execute(pool)
    .await
    .unwrap();

    sqlx::query(
        "CREATE TABLE IF NOT EXISTS observations(
                    id                         INTEGER   PRIMARY KEY AUTOINCREMENT,
                    telescope                  CHAR(20)  NOT NULL,
                    date                       DATE      NOT NULL,
                    starid                     INTEGER   NOT NULL,
                    FOREIGN KEY(starid) REFERENCES stars(id))",
    )
    .execute(pool)
    .await
    .unwrap();
}
