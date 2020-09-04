FROM roboxes/rhel6
COPY ./code/* /app/
CMD gcc /app/tetris.c -o /app/tetris
RUN ls /app/
RUN /app/tetris
