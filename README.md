# TCP Chat App — Clean Server Architecture (C++ / ASIO)

## Overview
This project is a **from-scratch chat application** built to practice **networking fundamentals, OOD, and clean architecture**.

The system consists of:
- **C++ TCP Server** built using **ASIO**
- **C# Client** that communicates with the server using a custom binary protocol over TCP

The goal was **not** to build the fastest way to get a working chat, but to design a **scalable, maintainable architecture** that can grow over time.

---

## What is a Chat App?
Any chat application must have two core parts:

- **Server**: accepts connections, manages users/groups, and routes messages
- **Client**: connects to the server, sends requests, and receives responses

Both sides must agree on:
- A **network connection** (TCP)
- A **protocol** (rules that define how data is sent and interpreted)

---

## High-Level Server Flow
Because this server is built on **TCP sockets**, the flow is as follows:

1. A client connects to the server
2. The server accepts the connection and creates a **dedicated socket**
3. A `Session` object wraps this socket and stores client-related data
4. Incoming bytes are parsed into **request objects**
5. Requests are routed and executed
6. Responses are sent back to the client

---

## Architecture Overview
The server follows a layered architecture:
Client
↓
TCP Socket Accepter Layer
↓
Session
↓
Parser
↓
Request Router
↓
Request Handlers
↓
Services
↓
Repositories

Each layer has **one clear responsibility**, making the system easier to understand and extend.

---

## Core Components

### TCP Socket Accepter Layer
- Listens for incoming TCP connections
- Creates a new socket for each client
- Initializes a `Session` for every accepted connection

---

### Session
- Wraps the TCP socket
- Stores client metadata (id, name, etc.)
- Exposes `read` and `write` operations
- Encapsulates all per-client networking logic

---

### Protocol Design
TCP sends **ordered bytes only**, so a protocol is required to define message boundaries and meaning.

Each request follows this format:

- **First 4 bytes**: `int32` → number of bytes the server should read next
- **Second 4 bytes**: `int32` → request type  
  - Example:
    - `4` → connect to group
    - `6` → send message to group
- **Remaining bytes**: request parameters (group id, message text, etc.)

[ length (4 bytes) ][ request_type (4 bytes) ][ parameters (N bytes) ]


---

### Parser
- Reads raw bytes from the session
- Applies protocol rules
- Converts bytes into a **Request object**
- Returns a pointer/reference to `RequestBase`
- Uses **polymorphism** to support multiple request types

---

### Request Base & Request Handlers
- All requests inherit from `RequestBase`
- Each request implements a single public method:

```cpp
Response execute();
```

### Request Examples
- `SendMessageRequest`
- `ConnectToGroupRequest`
- `OtherRequest...`

Each request:
- Contains its own logic
- Knows how to execute itself
- Returns a base `Response` object

---

### Request Base & Request Handlers
- All requests inherit from `RequestBase`
- Each request implements a single public method:

```cpp
Response execute();
```

Notes

I am not a networking or C++ expert, and there may be design flaws or improvements you can spot.
If you have feedback, ideas, or want to contribute — feel free to open an issue or comment.
