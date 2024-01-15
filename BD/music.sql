--
-- PostgreSQL database dump
--

-- Dumped from database version 15.4
-- Dumped by pg_dump version 15.4

-- Started on 2024-01-08 15:03:40

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 214 (class 1259 OID 16733)
-- Name: album; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.album (
    album_id integer NOT NULL,
    artist_id integer,
    name character varying(50),
    data_lansare date
);


ALTER TABLE public.album OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 16748)
-- Name: melodie; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.melodie (
    melodie_id integer NOT NULL,
    album_id integer,
    nume character varying(50),
    data_lansare date
);


ALTER TABLE public.melodie OWNER TO postgres;

--
-- TOC entry 226 (class 1259 OID 17094)
-- Name: album_top_melodii; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.album_top_melodii AS
 SELECT album.name,
    count(album.name) AS count
   FROM (public.melodie
     JOIN public.album ON ((melodie.album_id = album.album_id)))
  GROUP BY album.name
  ORDER BY (count(album.name)) DESC
 LIMIT 1;


ALTER TABLE public.album_top_melodii OWNER TO postgres;

--
-- TOC entry 215 (class 1259 OID 16736)
-- Name: artist; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.artist (
    artist_id integer NOT NULL,
    name character varying(50) NOT NULL
);


ALTER TABLE public.artist OWNER TO postgres;

--
-- TOC entry 216 (class 1259 OID 16739)
-- Name: gen_muzical; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.gen_muzical (
    gen_id integer NOT NULL,
    nume character varying(50)
);


ALTER TABLE public.gen_muzical OWNER TO postgres;

--
-- TOC entry 217 (class 1259 OID 16742)
-- Name: genuri_artisti; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.genuri_artisti (
    artist_id integer NOT NULL,
    gen_id integer NOT NULL
);


ALTER TABLE public.genuri_artisti OWNER TO postgres;

--
-- TOC entry 218 (class 1259 OID 16745)
-- Name: genuri_melodii; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.genuri_melodii (
    melodie_id integer NOT NULL,
    gen_id integer NOT NULL
);


ALTER TABLE public.genuri_melodii OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 16751)
-- Name: melodie_artist; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.melodie_artist (
    melodie_id integer NOT NULL,
    artist_id integer NOT NULL
);


ALTER TABLE public.melodie_artist OWNER TO postgres;

--
-- TOC entry 228 (class 1259 OID 17102)
-- Name: numar_genuri; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.numar_genuri AS
 SELECT count(*) AS count
   FROM public.gen_muzical;


ALTER TABLE public.numar_genuri OWNER TO postgres;

--
-- TOC entry 224 (class 1259 OID 16763)
-- Name: utilizator; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.utilizator (
    utilizator_id integer NOT NULL,
    username character varying(50),
    email character varying(50),
    parola character varying(50)
);


ALTER TABLE public.utilizator OWNER TO postgres;

--
-- TOC entry 227 (class 1259 OID 17098)
-- Name: numar_utilizatori; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.numar_utilizatori AS
 SELECT count(*) AS numar_total_utilizatori
   FROM public.utilizator;


ALTER TABLE public.numar_utilizatori OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 16754)
-- Name: playlist; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.playlist (
    playlist_id integer NOT NULL,
    utilizator_id integer,
    nume character varying(50)
);


ALTER TABLE public.playlist OWNER TO postgres;

--
-- TOC entry 222 (class 1259 OID 16757)
-- Name: playlist_melodie; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.playlist_melodie (
    playlist_id integer NOT NULL,
    melodie_id integer NOT NULL
);


ALTER TABLE public.playlist_melodie OWNER TO postgres;

--
-- TOC entry 223 (class 1259 OID 16760)
-- Name: urmaritori; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.urmaritori (
    utilizator_id integer NOT NULL,
    artist_id integer NOT NULL
);


ALTER TABLE public.urmaritori OWNER TO postgres;

--
-- TOC entry 225 (class 1259 OID 17090)
-- Name: urmaritori_delia; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.urmaritori_delia AS
 SELECT utilizator.username
   FROM (public.artist
     JOIN (public.utilizator
     JOIN public.urmaritori ON ((utilizator.utilizator_id = urmaritori.utilizator_id))) ON ((artist.artist_id = urmaritori.artist_id)))
  WHERE ((artist.name)::text = 'Delia'::text);


ALTER TABLE public.urmaritori_delia OWNER TO postgres;

--
-- TOC entry 3409 (class 0 OID 16733)
-- Dependencies: 214
-- Data for Name: album; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.album (album_id, artist_id, name, data_lansare) FROM stdin;
0	0	Orasul 511	2005-05-05
1	1	OTZL GLTZ	2022-07-20
2	0	Bonjour Madame	2022-05-22
3	1	Lololo	2021-02-11
4	2	Master of Pupets	1986-03-03
5	2	Metallica	1991-10-15
6	2	Reload	1997-02-04
7	3	Eine Kleine Nachtmusik	1787-08-10
8	4	JazzOmatic	2023-10-26
\.


--
-- TOC entry 3410 (class 0 OID 16736)
-- Dependencies: 215
-- Data for Name: artist; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.artist (artist_id, name) FROM stdin;
0	Alternosfera
1	Delia
2	Metallica
3	Mozart
4	Louis Armstrong
\.


--
-- TOC entry 3411 (class 0 OID 16739)
-- Dependencies: 216
-- Data for Name: gen_muzical; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.gen_muzical (gen_id, nume) FROM stdin;
0	jazz
1	rock
3	hiphop
4	pop
2	Clasic
\.


--
-- TOC entry 3412 (class 0 OID 16742)
-- Dependencies: 217
-- Data for Name: genuri_artisti; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.genuri_artisti (artist_id, gen_id) FROM stdin;
0	1
1	3
1	4
2	1
4	0
4	4
3	2
\.


--
-- TOC entry 3413 (class 0 OID 16745)
-- Dependencies: 218
-- Data for Name: genuri_melodii; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.genuri_melodii (melodie_id, gen_id) FROM stdin;
0	1
1	1
2	3
2	4
3	1
4	3
4	4
5	1
6	1
7	1
8	2
9	1
\.


--
-- TOC entry 3414 (class 0 OID 16748)
-- Dependencies: 219
-- Data for Name: melodie; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.melodie (melodie_id, album_id, nume, data_lansare) FROM stdin;
0	0	Orasul 511	2005-05-05
1	0	Wamintirile	2005-05-05
2	1	OTZL GLTZ	2022-07-20
3	2	Bonjour Madame	2022-05-22
4	3	Lololo	2021-02-11
5	4	Master of Pupets	1986-03-03
6	5	Enter Sandman	1991-10-15
7	6	Fuel	1997-02-04
8	7	eine Kleine Nachtmusik	1787-08-10
9	8	Lazy River	2023-10-26
\.


--
-- TOC entry 3415 (class 0 OID 16751)
-- Dependencies: 220
-- Data for Name: melodie_artist; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.melodie_artist (melodie_id, artist_id) FROM stdin;
0	0
1	0
2	1
3	0
4	1
5	2
6	2
7	2
8	3
9	4
\.


--
-- TOC entry 3416 (class 0 OID 16754)
-- Dependencies: 221
-- Data for Name: playlist; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.playlist (playlist_id, utilizator_id, nume) FROM stdin;
0	0	Rockereala
\.


--
-- TOC entry 3417 (class 0 OID 16757)
-- Dependencies: 222
-- Data for Name: playlist_melodie; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.playlist_melodie (playlist_id, melodie_id) FROM stdin;
0	0
0	1
0	3
0	5
0	6
0	7
\.


--
-- TOC entry 3418 (class 0 OID 16760)
-- Dependencies: 223
-- Data for Name: urmaritori; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.urmaritori (utilizator_id, artist_id) FROM stdin;
0	1
0	3
1	2
1	4
2	1
3	3
4	4
4	0
\.


--
-- TOC entry 3419 (class 0 OID 16763)
-- Dependencies: 224
-- Data for Name: utilizator; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.utilizator (utilizator_id, username, email, parola) FROM stdin;
0	Ivan Cosmin	ivan@gmail.com	1q2w3e
1	Malos Mihai	mihai@gmail.com	parola
2	Oancea	andre1@gmail.com	valoare
3	Ionel	cioban@yahoo.com	oileMele
4	Marcel	marcel@gmail.com	Margareta
\.


--
-- TOC entry 3229 (class 2606 OID 16767)
-- Name: album album_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.album
    ADD CONSTRAINT album_pkey PRIMARY KEY (album_id);


--
-- TOC entry 3231 (class 2606 OID 16769)
-- Name: artist artist_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.artist
    ADD CONSTRAINT artist_pkey PRIMARY KEY (artist_id);


--
-- TOC entry 3233 (class 2606 OID 16771)
-- Name: gen_muzical gen_muzical_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.gen_muzical
    ADD CONSTRAINT gen_muzical_pkey PRIMARY KEY (gen_id);


--
-- TOC entry 3235 (class 2606 OID 16773)
-- Name: genuri_artisti genuri_artisti_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genuri_artisti
    ADD CONSTRAINT genuri_artisti_pkey PRIMARY KEY (artist_id, gen_id);


--
-- TOC entry 3237 (class 2606 OID 16775)
-- Name: genuri_melodii genuri_melodii_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genuri_melodii
    ADD CONSTRAINT genuri_melodii_pkey PRIMARY KEY (melodie_id, gen_id);


--
-- TOC entry 3241 (class 2606 OID 16777)
-- Name: melodie_artist melodie_artist_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.melodie_artist
    ADD CONSTRAINT melodie_artist_pkey PRIMARY KEY (melodie_id, artist_id);


--
-- TOC entry 3239 (class 2606 OID 16779)
-- Name: melodie melodie_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.melodie
    ADD CONSTRAINT melodie_pkey PRIMARY KEY (melodie_id);


--
-- TOC entry 3245 (class 2606 OID 16781)
-- Name: playlist_melodie playlist_melodie_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.playlist_melodie
    ADD CONSTRAINT playlist_melodie_pkey PRIMARY KEY (playlist_id, melodie_id);


--
-- TOC entry 3243 (class 2606 OID 16783)
-- Name: playlist playlist_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.playlist
    ADD CONSTRAINT playlist_pkey PRIMARY KEY (playlist_id);


--
-- TOC entry 3247 (class 2606 OID 16785)
-- Name: urmaritori urmaritori_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.urmaritori
    ADD CONSTRAINT urmaritori_pkey PRIMARY KEY (utilizator_id, artist_id);


--
-- TOC entry 3249 (class 2606 OID 16787)
-- Name: utilizator utilizator_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.utilizator
    ADD CONSTRAINT utilizator_pkey PRIMARY KEY (utilizator_id);


--
-- TOC entry 3250 (class 2606 OID 16788)
-- Name: album album_artist_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.album
    ADD CONSTRAINT album_artist_id_fkey FOREIGN KEY (artist_id) REFERENCES public.artist(artist_id);


--
-- TOC entry 3251 (class 2606 OID 16793)
-- Name: genuri_artisti genuri_artisti_artist_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genuri_artisti
    ADD CONSTRAINT genuri_artisti_artist_id_fkey FOREIGN KEY (artist_id) REFERENCES public.artist(artist_id);


--
-- TOC entry 3252 (class 2606 OID 16798)
-- Name: genuri_artisti genuri_artisti_gen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genuri_artisti
    ADD CONSTRAINT genuri_artisti_gen_id_fkey FOREIGN KEY (gen_id) REFERENCES public.gen_muzical(gen_id);


--
-- TOC entry 3253 (class 2606 OID 16803)
-- Name: genuri_melodii genuri_melodii_gen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genuri_melodii
    ADD CONSTRAINT genuri_melodii_gen_id_fkey FOREIGN KEY (gen_id) REFERENCES public.gen_muzical(gen_id);


--
-- TOC entry 3254 (class 2606 OID 16808)
-- Name: genuri_melodii genuri_melodii_melodie_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genuri_melodii
    ADD CONSTRAINT genuri_melodii_melodie_id_fkey FOREIGN KEY (melodie_id) REFERENCES public.melodie(melodie_id);


--
-- TOC entry 3255 (class 2606 OID 16813)
-- Name: melodie melodie_album_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.melodie
    ADD CONSTRAINT melodie_album_id_fkey FOREIGN KEY (album_id) REFERENCES public.album(album_id);


--
-- TOC entry 3256 (class 2606 OID 16818)
-- Name: melodie_artist melodie_artist_artist_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.melodie_artist
    ADD CONSTRAINT melodie_artist_artist_id_fkey FOREIGN KEY (artist_id) REFERENCES public.artist(artist_id);


--
-- TOC entry 3257 (class 2606 OID 16823)
-- Name: melodie_artist melodie_artist_melodie_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.melodie_artist
    ADD CONSTRAINT melodie_artist_melodie_id_fkey FOREIGN KEY (melodie_id) REFERENCES public.melodie(melodie_id);


--
-- TOC entry 3259 (class 2606 OID 16828)
-- Name: playlist_melodie playlist_melodie_melodie_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.playlist_melodie
    ADD CONSTRAINT playlist_melodie_melodie_id_fkey FOREIGN KEY (melodie_id) REFERENCES public.melodie(melodie_id);


--
-- TOC entry 3260 (class 2606 OID 16833)
-- Name: playlist_melodie playlist_melodie_playlist_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.playlist_melodie
    ADD CONSTRAINT playlist_melodie_playlist_id_fkey FOREIGN KEY (playlist_id) REFERENCES public.playlist(playlist_id);


--
-- TOC entry 3258 (class 2606 OID 16838)
-- Name: playlist playlist_utilizator_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.playlist
    ADD CONSTRAINT playlist_utilizator_id_fkey FOREIGN KEY (utilizator_id) REFERENCES public.utilizator(utilizator_id);


--
-- TOC entry 3261 (class 2606 OID 16843)
-- Name: urmaritori urmaritori_artist_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.urmaritori
    ADD CONSTRAINT urmaritori_artist_id_fkey FOREIGN KEY (artist_id) REFERENCES public.artist(artist_id);


--
-- TOC entry 3262 (class 2606 OID 16848)
-- Name: urmaritori urmaritori_utilizator_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.urmaritori
    ADD CONSTRAINT urmaritori_utilizator_id_fkey FOREIGN KEY (utilizator_id) REFERENCES public.utilizator(utilizator_id);


-- Completed on 2024-01-08 15:03:40

--
-- PostgreSQL database dump complete
--

