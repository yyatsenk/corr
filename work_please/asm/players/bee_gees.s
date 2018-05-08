.name "ss"
.comment "sa, Ha, Japan's geography made this invasion plan obvious to the Japanese; they were able to predict the Allied invasion plans accurately and thus adjust their defensive plan, Operation Ketsugō, accordingly. The Japanese planned an all-out defense of Kyūshū, with little left in reserve for any subsequent defense operations.[12] Four veteran divisions were withdrawn from the Kwantung Army in Manchuria in March 1945 to strengthen the forces in Japan,[13] and 45 new divisions were activated between February and May 1945. Most were immobile formations for coastal defense, but 16 were high quality mobile divisions.[14] In all, there were 2.3 million Japanese Army troops prepared to defend the home islands, backed by a civilian militia of 28 million men and women. Casualty predictions varied widely, but were extremely high. The Vice Chief of the Imperial Japanese Navy General Staff, Vice Admiral Takijirō Ōnishi, predicted up to 20 million Japanese deaths.[15]"
	
sti	r1, %:live, %1			;change live by the right value
sti	r1, %:live2, %1			;change live by the right value
ld	%1, r3
ld	%33, r6
#While (r2 < 10)
forks:
add	r2, r3, r2		;increment r2
xor	r2, %15, r4		;if (r4) {carry = 0}
live2:
	live 	%4
zjmp	%:endwhile		;if (carry)
fork	%:forks
ld	%0, r4			;carry = 1
zjmp	%:forks
#EndWhile
endwhile:
ld	%0, r4			;carry = 1

live:
live %4
zjmp %:live
